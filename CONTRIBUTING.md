Contributing
============
Instructions on how to contribute to the codebase. **Remember to document progress in the notebook!**

Setup Environment
-----------------
Install the following software

- [Visual Studio Code](https://code.visualstudio.com/)
- [Git](https://git-scm.com/)
- Clang-Format (Bundled with 'Clang')

You will also need the following VSCode extensions:

- [VEX Robotics](https://marketplace.visualstudio.com/items?itemName=VEXRobotics.vexcode)
- [Clang-Format](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) (Requires Clang-Format to be installed seperately)
- [Clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) (Disable microsoft C/C++)

After installing the necessary software, [set up git on your machine](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup) and clone this project.

From there, in the project directory, create a file at `.vscode/settings.json` with (at least) the following entries:

```json
{
	"editor.formatOnSave": true,
    "editor.detectIndentation": false,
    "editor.insertSpaces": false,
    "editor.defaultFormatter": "xaver.clang-format",
	"clang-format.style": "file",
}
```

Style Guide
-----------
While the formatter will mostly take care of keeping the code consistent, programmers should also adhere to the following guidelines:

- Prefer `struct` for data structures and `class` when using traditional OOP features such as methods and private members 

- Use `snake_case` for variables & functions, `SCREAMING_CASE` for constants, and `PascalCase` for templates & class names

- Give variables meaningful names

- Use comments sparingly, only when a piece of code cannot be explained by reading it

- Avoid too much or too little whitespace

- Use section comments to seperate parts of code

- Create a seperate branch when creating large, breaking features or modifications. Create a pull request to merge into main branch

Following these guidelines will help the codebase be more organized and maintainable.