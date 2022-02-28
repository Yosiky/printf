# PRINTF

## Using
In order to use my function printf you need to write `make` in console.  
And copy file libftprintf.a in you directory.

## Description
The printf function supports these types like:
+ %c Prints a single character. 
+ %s Prints a string (as defined by the common C convention).
+ %p The void * pointer argument has to be printed in hexadecimal format.
+ %d Prints a decimal (base 10) number.
+ %i Prints an integer in base 10.
+ %u Prints an unsigned decimal (base 10) number.
+ %x Prints a number in hexadecimal (base 16) lowercase format.
+ %X Prints a number in hexadecimal (base 16) uppercase format.
+ %% Prints a percent sign.

Flags:  
`-` the output value is left-aligned within the minimum field width.  
`+` always specify a sign (plus or minus) for the displayed decimal numeric value.  
`space` put a space before the result if the first character of the value is not a sign.  
`#` 'alternative form' of value output.  
`0` pad the field to the width specified in the escape sequence width field with the character 0.  
Also you can use width and precision modifiers.
