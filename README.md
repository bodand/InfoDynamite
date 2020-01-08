<center><h1>InfoDynamite</h1></center>

---

# About

InfoDynamite is a small library which allows the discovery and evocation of foreign
C++ functions in a shared object/dll file. Cross platform, of course; supports
Windows and ELF platforms.

# Usage

Usage is easy, to call a function it is only required to follow these 3 easy steps: 
(more in-depth documentation is WIP)

1) Instantiate an `info::dynamite::DynamicLibrary` object.
   This takes the basename of the shared object, and only the basename, in the 
   style of link invocations like `-ldl` for `libdl.so`. The second parameter, 
   can be set to false to avoid the prepending of `lib` to the library name. 
   The extension is platform specifically determined to be `.dll` for Win, 
   `.dylib` for OSX, or otherwise `.so`.
   
2) Call `getFunction` on the object to get a `info::dynamite::DynamicFunction` object. 
   This takes the name of the function as it is in the source code, BUT without 
   return type and without parameter names, eg. `sqr_p(int*, int)`. Currently
   the formatting is required to be as that, `*` without space, `,` without space before
   and with after. 
   
3) Use `operator()`, `call`, or `callReturn<T>` with the required parameters on the
   `info::dynamite::DynamicFunction` object and voilà. The function is run.
   
# Documentation

Under construction; see you soon:tm:.   
   
# License

InfoDynamite is licensed under the BSD 3-Clause license, available for inspection in
the supplied `LICENSE` file.
The external dependency [`magic_enum`][me] is licensed under the MIT License, available for
inspection in the supplied `LICENSE.magic_enum` file.


[me]: https://github.com/Neargye/magic_enum
