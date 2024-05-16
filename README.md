# leveled-typing-test
A typing test in C that uses levels and has a vowel, consonant, and numbers mode. Levels 1, 2, and 3 alter the volume of text that is given. In numbers mode, the levels alter from having spaces, no spaces, or a hexadecimal number respectively.

## Installation
1. Download/fork/clone this repository.
2. In textreading.c, you'll have to find the `start_test()` function and change the absolute pathnames to where the 'texts' folder in your directory is for the respective files.
3. Go `cmake-build-debug/TypingTest.exe` and run the executable.
4. Have fun!

## Editing Textbank Files
If you want to add more text files, you'll have to download a .txt with a book inside of it. I'd recommend getting free ones from [Gutenberg](https://www.gutenberg.org/). All you'd have to do is (if you got it from Gutenberg) strip the header and table of contents, and then rename it textbank(#), assuming you include whatever amount of number files. Then in `start_test()` you'll want to change the `(rand() % 3) + 1` to whatever number of files your text files now contain.
