//Sivani Kommineni and Ankita Panchal

int isCommand(char *command, char *input);
#define Buffer_size 13312

void main() {
    while(1) {
       char input[Buffer_size];
       char buffer[Buffer_size];
       char txtInput[512];
       int sectorsRead, txtLength, i,j,k;
       char filename[7];
       char dir[512];

        for(i=0; i<512; i++) {
                input[i] = '\0';
                buffer[i] = '\0';
        }

        syscall(0, "A:>");
        syscall(1, input);

        if(isCommand("type",input)) {
            syscall(3, input+5, buffer, &sectorsRead);
            if(sectorsRead <= 0) {
                 syscall(0, "Invalid file\r\n");
                 
            }else{
            syscall(0, buffer);
          	syscall(0, "\r\n");
          }
        } else if(isCommand("exec", input)) {
            syscall(3, input+5, buffer, &sectorsRead);
            if(sectorsRead<=0) syscall(0, "Invalid file\r\n");
            else {
                    syscall(4, input+5);
            }        
        }   
      
        else if(isCommand(input, "dir\0")) {
            // list files in the directory
            syscall(2, dir, 2);
            for (i=0; i<512; i+=32) {
                if (dir[i] == '\0') continue;
                for (j=0; j<6; j++) {
                    filename[j] = dir[i+j];
                }
                filename[6] = '\0';
                syscall(0, filename);
                syscall(0, "\r\n");
            }
        } 
        else if(isCommand("del\0", input)){
            syscall(7, input+4);
        }
        else if(isCommand("copy\0", input)) {
            // copy a file
            for(i=5; i<512; i++) {
                if(input[i] == ' ') {
                    input[i] = 0;
                    i++;
                    break;
                }
            }
            syscall(3, input+5, buffer, &sectorsRead); // filename1
            if(sectorsRead<=0) syscall(0, "error: file not found\r\n");

            syscall(8, buffer, input+i, sectorsRead); // filename2
        } 
        else if(isCommand("create\0", input)) {
            // create a text file
            txtLength = 0;
            for(i=0; i<26; i++) { // max file length is 26 sectors
                // clear line input
                for(j=0; j<512; j++) {
                    txtInput[j] = '\0';
                }

                // read line
                syscall(1, txtInput);
                if(txtInput[0]=='\0') break;
                
                // add carriage return and newline to end of line
                for(j=0; j<510; j++) { // cap at 510 bytes to leave room for a carriage return and a newline
                    if(txtInput[j]=='\0') {
                        break;
                    }
                }
                txtInput[j++] = '\r';
                txtInput[j++] = '\n';   

                // add line to buffer
                for(k=0; k<j; k++) {
                    buffer[txtLength+k] = txtInput[k];
                }
                txtLength += j;
            }
            syscall(8, buffer, input+7, i);
        }
        else {
            syscall(0, "Command not recognized\r\n");
        }
    }
}
	
int isCommand(char *command, char *input) {
    while (*command != '\0' && *command != ' ' && *input != '\0' && *input != ' ') {
        if (*command != *input) {
            return 0; // false
        }
        command++;
        input++;
    }

    if(*command=='\0') return 1; // true
    else return 0;
}
