# Guess the Number Game (UDP)

This project is a simple **Guess the Number** game using **UDP** for communication, developed in **C** with **Winsock**. The server generates a random number between 1 and 100, and clients take turns guessing the number. The server provides feedback on each guess (higher, lower, or correct). The project also includes enhanced security features to block malicious activity, such as repeated invalid guesses.

---

### **Features**:

* **Simple Client-Server Communication Using UDP**: The server and multiple clients communicate via UDP protocol.
* **Random Number Generation**: The server generates a random number between 1 and 100 that clients must guess.
* **Multiplayer Support**: Multiple clients can connect to the server and participate simultaneously.
* **Security Features**:

  * **Input Validation**: Ensures the input is numeric and within the valid range (1-100).
  * **Rate-Limiting & IP Blocking**: Clients that make too many invalid guesses are temporarily blocked.
  * **Data Integrity**: Checksums are used to ensure the data transmitted between the client and server is not corrupted.
  * **Blocking Malicious Clients**: Clients that repeatedly send invalid guesses are blocked for a set period of time.

---

### **Prerequisites**:

Ensure that you have the following installed on your system:

* **C Compiler**: Ensure that **gcc** or **MinGW** is installed on your system. The server and client are written in **C** and compiled using **gcc**.
* **Winsock Library**: This project uses **Winsock** for networking, which is available in Windows by default.
* **Visual Studio Code (Optional)**: You can use an editor like **VS Code** for a smooth development experience, which is also configured with **C/C++ IntelliSense**.

---

### **Installation Instructions**:

#### **Step 1: Clone the Repository**

Clone the repository to your local machine (if using GitHub or any source control platform):

```bash
git clone <repository-url>
```

#### **Step 2: Install Required Tools**

Make sure that the following tools are installed:

* **MinGW** (for Windows users) or **gcc** for compiling C programs.
* **Windows SDK** (if not already installed) for compiling Winsock programs.

---

### **Build and Run Instructions**:

#### **Step 1: Compile the Server and Client**

For **Server**:

1. Open a terminal/command prompt in the directory containing **server.c**.
2. Run the following command to compile the server:

   ```bash
   gcc server.c -o server -lws2_32
   ```

   This command will create an executable file called **server.exe**.

For **Client**:

1. Open a terminal/command prompt in the directory containing **client.c**.
2. Run the following command to compile the client:

   ```bash
   gcc client.c -o client -lws2_32
   ```

   This command will create an executable file called **client.exe**.

#### **Step 2: Run the Server and Client**

**Start the Server**:

* Run the server executable in the terminal:

  ```bash
  ./server
  ```

  The server will start listening on port **41234**.

**Start the Client**:

* Open another terminal/command prompt window.
* Run the client executable:

  ```bash
  ./client
  ```

  Enter your guess (a number between 1 and 100) and interact with the server.

#### **Step 3: Multiplayer Mode**

You can start multiple instances of the client by running **client.exe** in different terminals. The server will handle multiple clients and notify them when a new target number is generated.

---

### **Project Structure**:

The project consists of the following files:

* **server.c**: The server-side code that generates the target number and handles client communication.
* **client.c**: The client-side code where users input their guesses and interact with the server.
* **c\_cpp\_properties.json**: Configuration file for Visual Studio Code's IntelliSense to work with C/C++.
* **package.json**: Node.js project configuration (if you're using a Node.js server/client as well).
* **README.md**: This file, which explains how to use the project and run it.

---

### **Security Features**:

1. **Input Validation**:

   * Ensures that the input is numeric and within the valid range (1-100). If the input is invalid (non-numeric or out of range), the client receives an error message.

2. **Rate-Limiting and IP Blocking**:

   * Clients that make **too many invalid guesses** in a short time are temporarily blocked for a specified duration (e.g., 10 minutes). The server tracks each client's guesses and blocks them after exceeding the **invalid guess limit**.

3. **Data Integrity (Checksum)**:

   * A checksum mechanism can be added to ensure that the data received from clients is not corrupted during transmission.

4. **Client Blocking**:

   * Clients who continuously send invalid guesses or other malicious inputs are blocked for a set period. Once blocked, they cannot send further guesses until the block time expires.

---

### **Troubleshooting**:

If you encounter any issues while running the project:

* **"Error creating socket"**:

  * Ensure that no other programs are using the same port (**41234**). You can change the port number in both **server.c** and **client.c** if needed.

* **"Error receiving data"**:

  * Ensure that the server is running before starting the client.
  * Double-check the server IP (127.0.0.1 for localhost) in the client code.

* **Firewall Issues**:

  * Make sure that your firewall is not blocking UDP traffic on port **41234**. You may need to allow UDP traffic for the application.

---

### **Limitations and Future Enhancements**:

1. **Limitations**:

   * **No Persistent Data**: The game session and client information are stored only in memory, which means all data is lost when the server shuts down.
   * **Basic Blocking**: The blocking mechanism is based only on invalid guesses, while other forms of malicious behavior are not yet handled.

2. **Future Enhancements**:

   * **Persistent Data Storage**: Save game sessions and client statistics (e.g., scores, guess history) to a file or database.
   * **Advanced Blocking**: Implement more sophisticated blocking mechanisms based on behavior patterns, not just invalid guesses.
   * **GUI Interface**: Add a graphical user interface (GUI) to make the game more user-friendly.
   * **Enhanced Security**: Implement encryption for communication between the client and server to prevent tampering and eavesdropping.

---

### **Conclusion**:

This project demonstrates the creation of a simple yet secure **Guess the Number** game using **UDP communication**. It includes basic security features such as input validation, rate-limiting, and client blocking to ensure a fair and secure gaming experience. While the project is functional and meets its objectives, there are opportunities for further improvements, especially in terms of user experience and security.
