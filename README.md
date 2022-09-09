# First case of study in Buffer Overflow and arbitrary code execution.
- How can a simple application be dangerous to information security if not well implemented.
- How to develop an exploit to this specific case.
- Possible solutions to avoid Buffer Overflow and arbitrary code execution. 
---
### **Warning**: This is **ONLY** for educational and professional purposes, it is not my responsability if any of this content is used with bad intentions or poor ethic. 
- _With great power comes great responsibility..._
- _The quieter you become, the more you are able to hear_
---
---
# First file &rarr; `vuln.c` 

In this file, we have a simple program which takes an input, store in a variable (or in a memory slot) and print it out what you've entered with, simple as that.
But there is an function named `vitoria()` and inside of its body there is a `printf()` function with "Parabens! vc conseguiu!"  ("Congratulations! you've made it!") as a parameter, here is my question:
- how to print this phrase without calling this function, just using this input?

Here comes the fun part...

By now you might have heard about stack and return addresses, right? If not... Basically when some function is called, we have to store the return address in the stack so the program return to the original point from where he departed, because our program is segmented or "divided" in various places along our RAM, that's why we need to store an address of return to keep going from where we left off from the "original" address.

So, about the input... when the funtion responsible for taking the input is called, in this case: `gets()`, after we prompted the input, the value is temporaly stocked in the stack, the program is expecting some value that has the size in bytes equal (or less) to expected to store in the stack, so... 50 chars (same as 50 bytes) or less.

- Whats happens if we try to pass this limit of 50 bytes?

We start invading space of other important information, pushing important values to other addresses and overwritting original information of that address, if the last information we have in the stack is the return address, so... 

- Where should the program return after we overwrited the original value of return?

If we are not aware if this, we could just simply crash the program and not executing arbitrary code, but this is to boring and easy to do, just spam a lot of characters and done... but if we do want to execute arbitrary code, we need to know `where` execute, i recommend to use some debugger to help you to know which address to redirect the return (x32dbg, IDA Pro, etc...), in this case, the address that i wanted to return was 0x00401460, which where start the declaration of my function in interest. After we know where to redirect the return, we need to create the proper payload or the exploit for it.

---
---
# Second File &rarr; ``exploit.py``

So, after all of this, if we want a classy aproach of the desired result, we need to develop a exploit for it, i choose to write in python for it's simplicity to write code, i just needed 2 lines of code to do the exploit ;) <br>

I created a variable that will carry the payload of bytes that i want to execute in my vulnerable program, and the function to print the payload, since the input of the vuln is expecting some bytes to print (or try to print...)

If you don't know how to run a python script, is: `python <name_of_the_file>.py`<br>
But that's not all, we need to call the program too so we can pass the payload correctly, for that, we use what is called "Pipe" represented by this character &rarr; | <br>
Now we run everything in a single line of command: `python exploit.py | ./vuln.exe` and after it, we have executed arbitrary code.