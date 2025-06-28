# **Guess the Number Game (UDP)**

This project is a simple **Guess the Number** game using UDP for communication, developed in **C/C++** with **Winsock**. The server generates a random number between 1 and 100, and clients take turns guessing the number. The server provides feedback on each guess (higher, lower, or correct).

---

## **Features**

* Simple client-server communication using UDP.
* Server handles multiple clients and provides feedback on their guesses.
* Security features:

  * Basic **input validation** for guesses.
  * **Rate-limiting** and **IP blocking** for clients making too many requests in a short period of time.
  * **Checksum** to ensure data integrity.

---

## **Prerequisites**

Make sure you have the following installed on your system:

1. **C Compiler**: Ensure that `gcc` or `MinGW` is installed on your system. The server and client are written in **C** and compiled using `gcc`.

2. **Winsock Library**: This project uses **Winsock** for networking, which is available in **Windows** by default.

3. **Visual Studio Code (Optional)**: You can use an editor like **VS Code** for a smooth development experience, which is also configured with **C/C++ IntelliSense**.

---

## **Installation Instructions**

### **Step 1: Clone the Repository**

Clone the repository to your local machine (if using GitHub or any source control platform):

```bash
git clone <repository-url>
```

### **Step 2: Install Required Tools**

Make sure that the following tools are installed:

* **MinGW** (for Windows users) or **gcc** for compiling C programs.
* **Windows SDK** (if not already installed) for compiling Winsock programs.

---

## **Build and Run Instructions**

### **Step 1: Compile the Server and Client**

1. **For Server**:

   * Open a terminal/command prompt in the directory containing `server.c`.
   * Run the following command to compile the server:

   ```bash
   gcc server.c -o server -lws2_32
   ```

   This command will create an executable file called `server.exe`.

2. **For Client**:

   * Similarly, open a terminal/command prompt in the directory containing `client.c`.
   * Run the following command to compile the client:

   ```bash
   gcc client.c -o client -lws2_32
   ```

   This command will create an executable file called `client.exe`.

---

### **Step 2: Run the Server and Client**

1. **Start the Server**:

   * Run the server executable in the terminal:

   ```bash
   ./server
   ```

   * The server will start listening on port `41234`.

2. **Start the Client**:

   * Open another terminal/command prompt window.
   * Run the client executable:

   ```bash
   ./client
   ```

   * Enter your guess (a number between 1 and 100), and interact with the server.

---

### **Step 3: Multiplayer Mode**

* You can start multiple instances of the client by running the `client.exe` in different terminals.
* The server will handle multiple clients and notify them when a new target number is generated.

---

## **Project Structure**

The project consists of the following files:

* **server.c**: The server-side code that generates the target number and handles client communication.
* **client.c**: The client-side code where users input their guesses and interact with the server.
* **c\_cpp\_properties.json**: Configuration file for Visual Studio Code's IntelliSense to work with C/C++.
* **package.json**: Node.js project configuration (if you're using a Node.js server/client as well).
* **README.md**: This file, which explains how to use the project and run it.

---

## **Security Features**

 **Input Validation**:

   * Ensures that the input is numeric and within the valid range (1-100).

---

## **Troubleshooting**

If you encounter any issues while running the project:

1. **"Error creating socket"**:

   * Ensure that no other programs are using the same port (`41234`). You can change the port number in both `server.c` and `client.c` if needed.

2. **"Error receiving data"**:

   * Ensure that the server is running before starting the client.
   * Double-check the server IP (`127.0.0.1` for localhost) in the client code.

3. **Firewall Issues**:

   * Make sure that your firewall is not blocking UDP traffic on the port `41234`. You may need to allow UDP traffic for the application.
