# Welcome to the ft_printf! ![score](https://img.shields.io/badge/0/100-5cb85c?style=for-the-badge) 
> ft_printf is the project, which recodes printf.

A format specifier follows this prototype :  

```
%[flags][width][.precision][length]specifier
```
It works in the following conversions :
| flags | length | specifier |
| - | - | - |
| `-0# +` | `l ll h hh` | `nfgecspdiuxX%` |
<br/>


<div align = "center">
    <b>The relationship chart between length and specifier</b>

| length | `d` `i` |   `u` `x` `X`   |           `f` `e` `g`           | `c` | `s` | `p` | `n` |
|    -   |    -    |        -        |                -                |  -  |  -  |  -  |  -  |
| (none) | int     | unsigned int    | double | int | char * | void * | int * |
|   hh   | signed char | unsigned char ||||                    | signed char * |
|    h   | short int | unsigned short int ||||                 | short int * |
|    l   | long int | unsigned long int || wint_t | wchar_t * || long int * |
|   ll   | long long int | unsigned long int || | | | long long int * |

</div>

## Tester

* **pft** by [gavinfielder](https://github.com/gavinfielder)  

    ```shell
    git clone https://github.com/gavinfielder/pft.git pft && echo "pft/" >> .gitignore
    ```

* **PFT_2019** by [cclaude42](https://github.com/cclaude42)  
    
    ```shell
    git clone https://github.com/gavinfielder/pft.git pft_2019 && echo "pft_2019/" >> .gitignore && cd pft_2019 && rm unit_tests.c && rm options-config.ini && git clone https://github.com/cclaude42/PFT_2019.git temp && cp temp/unit_tests.c . && cp temp/options-config.ini . && rm -rf temp
    ```

* **ft_printf_test** by [HappyTramp](https://github.com/HappyTramp)  
    
    ```shell
    git clone https://github.com/HappyTramp/ft_printf_test.git
    ```

* **printf-tester** by [AntoineBourin](https://github.com/AntoineBourin)  
    
    ```shell
    git clone https://github.com/AntoineBourin/printf-tester.git
    ```

* **42TESTERS-PRINTF** by [Mazoise](https://github.com/Mazoise/42TESTERS-PRINTF)  
    
    ```shell
    git clone https://github.com/Mazoise/42TESTERS-PRINTF.git
    ```

* **42cursus-printf-test-2019** by [ggjulio](https://github.com/ggjulio/)  
    
    ```shell
    git clone https://github.com/ggjulio/42cursus-printf-test-2019.git
    ```

* **ftprintfdestructor** by [t0mm4rx](https://github.com/t0mm4rx)  
    
    ```shell
    git clone https://github.com/t0mm4rx/ftprintfdestructor.git && cd ftprintfdestructor && sh run.sh ..
    ```

* **printf_lover_v2** by [charMstr](https://github.com/charMstr/)  
    
    ```shell
    git clone https://github.com/charMstr/printf_lover_v2.git
    ```

---

## Mandatory part

* The prototype of ft_printf should be int ft_printf(const char *, ...);
* You have to recode the libc’s printf function
* It must not do the buffer management like the real printf
* It will manage the following conversions: `cspdiuxX%`
* It will manage any combination of the following flags: `-0.*` and minimum field width with all conversions
* It will be compared with the real printf
* You must use the command ar to create your librairy, using the command libtool is forbidden.



---

## Bonus part

* If the Mandatory part is not perfect don’t even think about bonuses
* You don’t need to do all the bonuses
* Manage one or more of the following conversions: `nfge`
* Manage one or more of the following flags: `l ll h hh`
* Manage all the following flags: `# +` (yes, one of them is a space)