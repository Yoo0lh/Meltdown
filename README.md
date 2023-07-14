# Meltdown 

![Image](/images/meltdown.jpeg "meltdawn")
Meltdown is a hardwer side-channel attack against modern CPU microprocessore (bypass speculative execution)that it can allow to read unprivileged data or memeory of other processor
Meltdown is a hardware side-channel attack against modern **CPU** microprocessore (**bypass speculative execution**)that it can allow to read unprivileged data or memory of other processor.

# Speculative Execution
also know as **Dynamic Execution**, to understand the significance of the Meltdown attack and how much is it amazing , it is mandatory to came across the speculative execution concept. this optimization technic widely used by the modern processors, allow them to predictively fetch and execute next instruction before knowing if the instruction is correct or not and that happen to provide some performance to processor.

```c
#include <stdio.h>
int main() {
    int numbers[] = {3, 8, 2, 10, 6};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < length; i++) {
        int curr = numbers[i];
        if (curr > 5) {
            printf("%d is greater than 5\n", curr);
            // some other codes to be execute 
        }
        printf("Processing number: %d\n", curr);
        // some other codes to be execute 
    }
    return 0;
}
```
int the previous example there is a loop iterate on array and check
if the number is greater or less than 5.</br>
1 - fetch the first number from the array. </br>
2 -  speculative execution predict that the number will be greater than 5 so it start </br>execution the code that handle the number greater than 5.</br>
3 - meanwhile it start continue fetching the next number from the array .</br>
4 - if the prediction was correct and the number is greater than 5 the code that handle the number is greater than 5 continue the execution .</br>
5 - if the prediction was not correct and number is less than 5 the code that </br>handle that the number is greater than 5 the speculative execution discard  and the correct code be taken .</br>
6 - repeat for the next number in the array.

speculative execution allowed the process speculatively execute the code greater than 5. </br>

modern **CPU** are all pipelined, which mean's they're capable of executing multiple instruction in parallel.
![Image](/images/pipeline.svg.png "pipeline")

the green block presents such as if-else, feching the next set of instruction related with that branche and being specliativly execute them before the next instruction can be detected, int the diagram above the speculative instruction presented by the purle box 

now before explaining why speculative execution is important, let's explain what out-of-order execution is (weve be), because it is an essential concept for understanding speculative execution.

## Out of Order Election  (OoOE)
it's a technique used by modern processor to optimize instruction and improve performance, in a sequential program, instructions are executed on by one in the **order** of the code. however **out-of-order execution** allows, the processor to dynamically  change the order of the instruction at runtime .
for example if we have those two lines of codes expecting the **CPU** will execute them one after the other by that not what happened because most modern **CPU's** will execute theme them at the same time that's called (out of order execution).
```c
	int x = 13 + 37;
	int y = 42 + 0;
```
out of order execution allows the process to find independent instruction and execute then in the same time, even if they 
specified in a sequential in the code, by changing the order of instruction dynamically, the process can effectively utilize the available resources for execution


### Why Speculative Execution is  importante for the CPU ?
before out of order execution was invented, CPUs was in order designs, instructions excused in the order they we received, 
with no attempts to order they received, or executed them more efficiently, one of the major problem with in order execution is that the pipeline stall stop the entire CPU until the issue is resolved.
one of the other reasons behind the development of speculative execution is increasing the gap between CPU speed and memory speed, as processors become much faster, the different between CPU clock speed and the time it took to access data form main memory become more bigger and bigger. as the following graph show.

![Image](/images/gap-performance.png "gap-performance")
> if the memory could match the performance of the CPU there would be no need for caches

caches are high speed and small pool memory in the CPU that store data to read more deeply on caches check [this](https://www.extremetech.com/extreme/188776-how-l1-and-l2-cpu-caches-work-and-why-theyre-an-essential-part-of-modern-chips) 

# Implication of meltdown 
meltdown has significant implication for system security, as it exposes the potential for malicious impact to extract sensitive data from protected memory on the system, the attacker can bypass memory isolation mechanism, such as virtual memory, to gain unauthorized access to sensitive data.</br>
the operation system rely on memory  isolation to prevent unauthorized  access to sensitive data, for example, user application are kept isolated from each other and from the **kernel memory space**, meltdown break this access data from other process.

check this for more [information](https://en.wikipedia.org/wiki/Kernel_page-table_isolation).

```c
unsigned long long meltdown(unsigned long long address) {
  unsigned long long start_time, end_time;
  start_time = clock();
  usleep(0.1);
  end_time = clock();
  return (end_time - start_time);
}
int main() {
  unsigned long long address = 0xfb61b000; // the addres to be access
  unsigned long long time_taken;
  char *address_string = "0xfb61b000";
  time_taken = meltdown(address); //cach time
  printf("Time taken to access address %s: %llu \n",address_string,
  time_taken);
  return 0;
}
```
the meltdown function check time to access the memory location `0xfb61b000` , if the location is cached then the meltdown function will return a small time, if it not it will return a longer time. 

# Mitigation
there are several **mitigation** techniques have been developed to stop the meltdown vulnerability and microarchitectural attacks .
### Softwer Pactches 
have been developed by **OS** vendors to mitigate the meltdown vulnerability, this patches typically include changes to the **kernel** and memory management mechanism to develop memory isolation and prevent unauthorized access to protected data .
### Microcode Updates
CPU vendors have been provided **microcode** updates that introduce changes to the processor behavior and speculative execution mechanism. 

### Kernel Page Table Isolation (KPTI)
is a technique that aims to protect the kernel memory from authorized access, it includes isolating the **kernel page tables** from user space process , preventing speculative execution attack from accessing sensitive data in the kernel, **KPTI** have been implemented in various os as defense against meltdown and microarchitectural vulnerability 

![Image](/images/Kernel_page-table_isolation.svg "kernel-page-tabel")

one set of page table for use n kernel mode includes both kernel space and user space the second set of page table for use in user mode contain a copy of user space and minimal set of kernel space handling system calls and interrupts 