\# Module 5: TCP File Server and Client



\## Problem Statement



The goal of this assignment is to develop a client-server application in C using TCP sockets. The client requests a text file by sending its filename to the server. The server reads the requested file and returns its contents to the client. The server must reject invalid filenames, report files that cannot be opened, and enforce a maximum file size of 2048 bytes.



\## Describe the Solution



The solution consists of two programs: `server.c` and `client.c`.



\- \*\*Server:\*\* Uses Windows Winsock to listen for TCP connections on port 8080. It receives a filename from the client, validates the filename, attempts to open the requested file, and sends the file contents if the file is within the size limit.

\- \*\*Client:\*\* Connects to the server on the local computer, prompts the user for a filename, sends the request, and prints the server's response.

\- \*\*Error handling:\*\* The server rejects invalid paths, reports missing or inaccessible files, and refuses files larger than 2048 bytes.

\- \*\*Graceful shutdown:\*\* The server handles Ctrl+C and displays a shutdown confirmation.



The programs were compiled using GCC with the Winsock library (`-lws2\_32`).



\## Pros and Cons



\### Pros

\- Uses TCP for reliable communication between the client and server.

\- Handles missing files, invalid filenames, and oversized files.

\- Limits file access to filenames in the server's working directory rather than accepting arbitrary paths.

\- Supports graceful server shutdown.



\### Cons

\- The server handles one client at a time.

\- The server and client are designed for Windows using Winsock.

\- The server does not support encrypted communication or user authentication.



\## Testing and Screenshots



The following tests were performed:



1\. \*\*Successful file request:\*\* Requested `hello.txt` and received its contents.

2\. \*\*Missing file:\*\* Requested `missing.txt` and received an error message.

3\. \*\*Oversized file:\*\* Requested `large.txt` and received an error because it exceeded 2048 bytes.

4\. \*\*Invalid filename:\*\* Requested `..\\secret.txt` and received an invalid filename error.

5\. \*\*Graceful shutdown:\*\* Pressed Ctrl+C and confirmed that the server shut down gracefully.



Screenshots documenting these tests are included with the submission.

