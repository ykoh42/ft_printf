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

**The relationship chart between length and specifier**
| length | `d` `i` | `u` `o` `x` `X` | `f` `F` `e` `E` `g` `G` `a` `A` | `c` | `s` | `p` | `n` |
|    -   |    -    |        -        |                -                |  -  |  -  |  -  |  -  |
| (none) | int | unsigned int | double | int | char * | void * | int * |
|   hh   | signed char | unsigned char ||||                    | signed char * |
|    h   | short int | unsigned short int ||||                 | short int * |
|    l   | long int | unsigned long int || wint_t | wchar_t * || long int * |
|   ll   | long long int | unsigned long int || | | | long long int * |


## Tester

- **Tester** by [whoswho](links)  

    ```shell
    git clone url.git
    ```



---

## Mandatory part

### Rules


---

## Bonus part


### Rules

ㅎㅎ