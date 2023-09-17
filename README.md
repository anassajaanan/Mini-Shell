# **Minishell**

Minishell is a Unix shell implementation developed as part of the 42 school curriculum. This project, undertaken collaboratively by **[Muna](https://github.com/anassajaanan)**, stands out due to its unique use of Recursive Descent Parsing, which serves as the foundation for robust command interpretation and execution.

## **Table of Contents**

- **[Features](#features)**
- **[Recursive Descent Parsing](#recursive-descent-parsing)**
- **[Usage](#usage)**
- **[Installation](#installation)**
- **[Contributing](#contributing)**
- **[License](#license)**

## **Features**

Minishell offers a wide range of features that make it a versatile and powerful Unix shell:

- **Basic Shell Commands**: Minishell supports a variety of fundamental Unix shell commands such as **`ls`**, **`cd`**, **`echo`**, **`pwd`**, and many others.
- **Piping and Redirection**: You can employ pipes (**`|`**) to connect commands and efficiently redirect input/output using **`<`**, **`>`**, and **`>>`**.
- **Error Handling**: Minishell provides informative error messages, making debugging easier and more effective.
- **Built-in Commands**: Several built-in commands are at your disposal, including **`exit`**, **`env`**, **`export`**, and **`unset`**.

## **Recursive Descent Parsing**

One of Minishell's most defining features is its utilization of Recursive Descent Parsing (RDP). RDP is a top-down parsing technique that empowers Minishell to efficiently interpret and execute user commands.

### **How RDP Works in Minishell**

1. **Lexical Analysis**: The input command undergoes lexical analysis, resulting in its tokenization into a sequence of tokens, which include command names, arguments, and operators.
2. **Parsing**: Minishell's RDP engine parses the tokenized input by performing a recursive descent through the grammar rules of the shell language. This process culminates in the creation of a tree data structure that meticulously represents the command's structure.
3. **Execution**: Following parsing, Minishell proceeds to execute the commands by traversing the parsed tree, ensuring precise adherence to the specified sequence of operations.

### **Benefits of RDP**

- **Human-Readable Grammar**: RDP facilitates the creation of a clear and human-readable grammar representation, enhancing the ease of maintaining and extending the shell's functionality.
- **Error Recovery**: Minishell's RDP engine exhibits robustness by being able to recover from certain syntax errors, significantly enhancing the user experience.

## **Usage**

To harness the capabilities of Minishell, proceed as follows:

1. **Clone the Repository**:
    
    ```bash
    git clone https://github.com/anassajaanan/Mini-Shell.git
    ```
    
2. **Build the Project**:
    
    ```bash
    cd Mini-Shell
    make
    ```
    
3. **Run Minishell**:
    
    ```bash
    ./minishell
    ```
    
4. **Begin Your Minishell Journey**:
    
    You can now start using Minishell to run commands and explore its plethora of features.
    
    ```bash
    $ ./minishell
    ```
    

## **Installation**

To install Minishell on your system, you'll need to follow these simple steps:

1. **Clone the Repository**:
    
    ```bash
    git clone https://github.com/anassajaanan/Mini-Shell.git
    ```
    
2. **Build the Project**:
    
    ```bash
    cd Mini-Shell
    make
    ```
    
3. **Launch Minishell**:
    
    ```bash
    ./minishell
    ```
    
4. **Begin Your Minishell Journey**:
    
    You can now start using Minishell to run commands and explore its plethora of features.
    

## **Contributing**

Both [Me](https://github.com/anassajaanan) and [Muna](https://github.com/anassajaanan) welcome contributions to the Minishell project! If you have ideas for enhancements, bug fixes, or new features, please feel free to open an issue or submit a pull request. For substantial changes, we recommend initiating a discussion in the issue tracker before proceeding.
