# CoutToLog

Allow to use std::cout as a logger with timestamps. 

* Wrapper inheriting from `std::streambuf` (usable with any `std::basic_ios<char>`)
* Windows only
* Built with v80 (compatible with higher toolsets)

## Usage

 Declare a `CoutToLog` instance in the scope where `std::cout` is desired to act as a logger.
Parameters are..
1. Log file path
2. *\<optional\>* Specific `std::basic_ios<char>` to replace
3. *\<optional\>* Log file opening mode

```cpp
int main()
{
  // Setup redirection
  CoutToLog redirect1("app.log");
  CoutToLog redirect2("app_errors.log", std::cerr, std::ios::app);

  // execute program...
    // std::cout output will be redirected to app.log
    // std::cerr output will be redirected to app_errors.log
    
  return 0; // redirections deallocated at the end of the scope
}
```

**Credits to [this guy on StackOverflow](https://stackoverflow.com/a/22119115/3038149)**