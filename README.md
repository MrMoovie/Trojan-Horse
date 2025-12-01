BLUE TEAM:
1. Static Analysis - 'Strings' command
   In the binary code `run`, there is a way to extract strings (by their unique signature). if the code wants to send to the ATTACKER a message, and it's defined as <char *> it can be easily identified as an intrusion.
   using he command `Strings <file>` We can easily find the strings in the binary code.
   
   <img width="517" height="276" alt="image" src="https://github.com/user-attachments/assets/c793691d-6ace-47cf-81e3-cb1ee14da2d6" />

2. Network Intrusion Detection System - NIDS
   Using tools like `Wiershark` we can easily see the plain text sent over the network, like "rs is ready" or even the bash scripts in the reverse shell. In addition if we use ports like `port: 4444` which is not a standart port for a server, it can be a sign of an intrusion, we send a RST signal, and the connection is severed.

   Problems:
    - Plain text
    - Unusual ports

   <img width="458" height="383" alt="image" src="https://github.com/user-attachments/assets/10f79aac-72f4-4c2b-82ef-84246724183e" />

3. Process analisys
   Using commands like `pstree` or `ps aux --forest` we can see the tree of each process. Meaning - we can see each process and his children, like:
```
   root      1082  0.0  0.1  /usr/sbin/sshd
   user      1402  0.0  0.1   \_ -bash
   user      4444  0.0  0.0       \_ ./Trojan      <-- suspicious name
   root      4445  0.0  0.0           \_ /bin/bash  <-- suspicious child
```
   
   

RED TEAM:
1. The solution is using an encryption, and decrypting right before the command execusion:
   
   e.g.
   
   
   Translating characters into HEX:
       
       "bin/bash" = 62-69-6e-2f-62-61-73-68
   using XOR and the key 0x42:
   
       (0x62-0x69-0x6e-0x2f-0x62-0x61-0x73-0x68) XOR (0x42) = 0x20-0x2b-0x2c-0x6d-0x20-0x23-0x31-0x2a
   b -> 0x20, i-> 0x2b, n -> 0x2c, / -> 0x6d, b -> 0x20. a -> 0x23, s -> 0x31. h -> 0x2a.
   
   and that's how we write it in the code:

 ``` C
   char hello[] = {0x20, 0x2b, 0x2c, 0x6d, 0x20, 0x23, 0x31, 0x2a, 0x00};
 ```
   Then in each place we decrypt using the next function:

``` C
   void decrypt(char *input, int len, char key) {
        for (int i = 0; i < len; i++) {
            input[i] = input[i] ^ key;
        }
    }
    char shell_cmd[] = {0x20, 0x2b, 0x2c, 0x6d, 0x20, 0x23, 0x31, 0x2a, 0x00}; 
    decrypt(shell_cmd, 8, 0x42);
    execve(shell_cmd, ...);
```

2. The solution yet again it an encryption before we send the data, and of course decryption upon recieving. The quickest way it to use encryption like XOR above.

   solution:
    - Encryption (like SSL/TSL or even XOR) 
    - Common ports like 80/443 on the target

``` C

```
``` Python
ATTACKER_PORT = 443
```


   
   

