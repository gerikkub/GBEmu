# 1 "source/video.c"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "source/video.c"
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 378 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 385 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 386 "/usr/include/sys/cdefs.h" 2 3 4
# 379 "/usr/include/features.h" 2 3 4
# 402 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 403 "/usr/include/features.h" 2 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/stdio.h" 2 3 4

# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 121 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 122 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 36 "/usr/include/stdio.h" 2 3 4
# 44 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 64 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 74 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 31 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 82 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 32 "/usr/include/libio.h" 2 3 4
# 49 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 50 "/usr/include/libio.h" 2 3 4
# 144 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 154 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 177 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 245 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 293 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 302 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 338 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 390 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 434 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 75 "/usr/include/stdio.h" 2 3 4




typedef __gnuc_va_list va_list;
# 90 "/usr/include/stdio.h" 3 4
typedef __off_t off_t;
# 102 "/usr/include/stdio.h" 3 4
typedef __ssize_t ssize_t;







typedef _G_fpos_t fpos_t;




# 164 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 165 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));




extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));








extern FILE *tmpfile (void) ;
# 209 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
# 227 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 252 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 266 "/usr/include/stdio.h" 3 4






extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 295 "/usr/include/stdio.h" 3 4

# 306 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
# 319 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));








extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

# 412 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 443 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 463 "/usr/include/stdio.h" 3 4








extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 494 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 522 "/usr/include/stdio.h" 3 4









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 550 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 561 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 594 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
# 638 "/usr/include/stdio.h" 3 4
extern char *gets (char *__s) __attribute__ ((__deprecated__));


# 665 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;








extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

# 737 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

# 773 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 792 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 815 "/usr/include/stdio.h" 3 4

# 824 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;








extern void perror (const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 854 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 873 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 913 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 943 "/usr/include/stdio.h" 3 4

# 2 "source/video.c" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 32 "/usr/include/stdlib.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 324 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 3 4
typedef int wchar_t;
# 33 "/usr/include/stdlib.h" 2 3 4








# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 42 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 64 "/usr/include/bits/waitstatus.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 36 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 37 "/usr/include/endian.h" 2 3 4
# 60 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 28 "/usr/include/bits/byteswap.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 29 "/usr/include/bits/byteswap.h" 2 3 4






# 1 "/usr/include/bits/byteswap-16.h" 1 3 4
# 36 "/usr/include/bits/byteswap.h" 2 3 4
# 44 "/usr/include/bits/byteswap.h" 3 4
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
# 108 "/usr/include/bits/byteswap.h" 3 4
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
# 61 "/usr/include/endian.h" 2 3 4
# 65 "/usr/include/bits/waitstatus.h" 2 3 4

union wait
  {
    int w_status;
    struct
      {

 unsigned int __w_termsig:7;
 unsigned int __w_coredump:1;
 unsigned int __w_retcode:8;
 unsigned int:16;







      } __wait_terminated;
    struct
      {

 unsigned int __w_stopval:8;
 unsigned int __w_stopsig:8;
 unsigned int:16;






      } __wait_stopped;
  };
# 43 "/usr/include/stdlib.h" 2 3 4
# 67 "/usr/include/stdlib.h" 3 4
typedef union
  {
    union wait *__uptr;
    int *__iptr;
  } __WAIT_STATUS __attribute__ ((__transparent_union__));
# 95 "/usr/include/stdlib.h" 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;







__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;


# 139 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;




extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;





extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

# 305 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 27 "/usr/include/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
# 60 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;
# 98 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;
# 115 "/usr/include/sys/types.h" 3 4
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 132 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 57 "/usr/include/time.h" 3 4


typedef __clock_t clock_t;



# 73 "/usr/include/time.h" 3 4


typedef __time_t time_t;



# 91 "/usr/include/time.h" 3 4
typedef __clockid_t clockid_t;
# 103 "/usr/include/time.h" 3 4
typedef __timer_t timer_t;
# 133 "/usr/include/sys/types.h" 2 3 4
# 146 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 147 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
# 194 "/usr/include/sys/types.h" 3 4
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));
# 219 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/sys/select.h" 1 3 4
# 30 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 22 "/usr/include/bits/select.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/select.h" 2 3 4
# 31 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/sigset.h" 1 3 4
# 22 "/usr/include/bits/sigset.h" 3 4
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;
# 34 "/usr/include/sys/select.h" 2 3 4



typedef __sigset_t sigset_t;





# 1 "/usr/include/time.h" 1 3 4
# 120 "/usr/include/time.h" 3 4
struct timespec
  {
    __time_t tv_sec;
    __syscall_slong_t tv_nsec;
  };
# 44 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/time.h" 1 3 4
# 30 "/usr/include/bits/time.h" 3 4
struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };
# 46 "/usr/include/sys/select.h" 2 3 4


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 64 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 96 "/usr/include/sys/select.h" 3 4

# 106 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 118 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 131 "/usr/include/sys/select.h" 3 4

# 220 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/sysmacros.h" 1 3 4
# 24 "/usr/include/sys/sysmacros.h" 3 4


__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 58 "/usr/include/sys/sysmacros.h" 3 4

# 223 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 270 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 21 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 22 "/usr/include/bits/pthreadtypes.h" 2 3 4
# 60 "/usr/include/bits/pthreadtypes.h" 3 4
typedef unsigned long int pthread_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;





typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
# 90 "/usr/include/bits/pthreadtypes.h" 3 4
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    short __spins;
    short __elision;
    __pthread_list_t __list;
# 124 "/usr/include/bits/pthreadtypes.h" 3 4
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;

  } __data;
# 211 "/usr/include/bits/pthreadtypes.h" 3 4
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 271 "/usr/include/sys/types.h" 2 3 4



# 315 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));




extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));









extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;










extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__));

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));




extern void cfree (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 493 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 513 "/usr/include/stdlib.h" 3 4


extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 530 "/usr/include/stdlib.h" 3 4





extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));













extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));






extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;

# 578 "/usr/include/stdlib.h" 3 4
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 606 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 620 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 642 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 663 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 712 "/usr/include/stdlib.h" 3 4





extern int system (const char *__command) ;

# 734 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 752 "/usr/include/stdlib.h" 3 4



extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 775 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;



__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;







extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;




__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;

# 812 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));






extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));








extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 899 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 951 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


# 1 "/usr/include/bits/stdlib-float.h" 1 3 4
# 956 "/usr/include/stdlib.h" 2 3 4
# 968 "/usr/include/stdlib.h" 3 4

# 3 "source/video.c" 2
# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 4 "source/video.c" 2
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4








# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 38 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/bits/time.h" 1 3 4
# 42 "/usr/include/time.h" 2 3 4
# 131 "/usr/include/time.h" 3 4


struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};








struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };


struct sigevent;
# 186 "/usr/include/time.h" 3 4



extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));

# 221 "/usr/include/time.h" 3 4
# 1 "/usr/include/xlocale.h" 1 3 4
# 27 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 222 "/usr/include/time.h" 2 3 4

extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 236 "/usr/include/time.h" 3 4



extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));





extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));





extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));







extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;





extern int stime (const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
# 319 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 334 "/usr/include/time.h" 3 4
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
# 430 "/usr/include/time.h" 3 4

# 5 "source/video.c" 2
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/omp.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/omp.h" 3 4
typedef struct
{
  unsigned char _x[4]
    __attribute__((__aligned__(4)));
} omp_lock_t;

typedef struct
{
  unsigned char _x[16]
    __attribute__((__aligned__(8)));
} omp_nest_lock_t;


typedef enum omp_sched_t
{
  omp_sched_static = 1,
  omp_sched_dynamic = 2,
  omp_sched_guided = 3,
  omp_sched_auto = 4
} omp_sched_t;
# 62 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/omp.h" 3 4
extern void omp_set_num_threads (int) __attribute__((__nothrow__));
extern int omp_get_num_threads (void) __attribute__((__nothrow__));
extern int omp_get_max_threads (void) __attribute__((__nothrow__));
extern int omp_get_thread_num (void) __attribute__((__nothrow__));
extern int omp_get_num_procs (void) __attribute__((__nothrow__));

extern int omp_in_parallel (void) __attribute__((__nothrow__));

extern void omp_set_dynamic (int) __attribute__((__nothrow__));
extern int omp_get_dynamic (void) __attribute__((__nothrow__));

extern void omp_set_nested (int) __attribute__((__nothrow__));
extern int omp_get_nested (void) __attribute__((__nothrow__));

extern void omp_init_lock (omp_lock_t *) __attribute__((__nothrow__));
extern void omp_destroy_lock (omp_lock_t *) __attribute__((__nothrow__));
extern void omp_set_lock (omp_lock_t *) __attribute__((__nothrow__));
extern void omp_unset_lock (omp_lock_t *) __attribute__((__nothrow__));
extern int omp_test_lock (omp_lock_t *) __attribute__((__nothrow__));

extern void omp_init_nest_lock (omp_nest_lock_t *) __attribute__((__nothrow__));
extern void omp_destroy_nest_lock (omp_nest_lock_t *) __attribute__((__nothrow__));
extern void omp_set_nest_lock (omp_nest_lock_t *) __attribute__((__nothrow__));
extern void omp_unset_nest_lock (omp_nest_lock_t *) __attribute__((__nothrow__));
extern int omp_test_nest_lock (omp_nest_lock_t *) __attribute__((__nothrow__));

extern double omp_get_wtime (void) __attribute__((__nothrow__));
extern double omp_get_wtick (void) __attribute__((__nothrow__));

void omp_set_schedule (omp_sched_t, int) __attribute__((__nothrow__));
void omp_get_schedule (omp_sched_t *, int *) __attribute__((__nothrow__));
int omp_get_thread_limit (void) __attribute__((__nothrow__));
void omp_set_max_active_levels (int) __attribute__((__nothrow__));
int omp_get_max_active_levels (void) __attribute__((__nothrow__));
int omp_get_level (void) __attribute__((__nothrow__));
int omp_get_ancestor_thread_num (int) __attribute__((__nothrow__));
int omp_get_team_size (int) __attribute__((__nothrow__));
int omp_get_active_level (void) __attribute__((__nothrow__));

int omp_in_final (void) __attribute__((__nothrow__));
# 6 "source/video.c" 2


# 1 "source/main.h" 1



# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 5 "source/main.h" 2



static void* malloc_line(int x,int line,int file){
 printf("Malloc called on line %d in file %d\n",line,file);
 return malloc(x);
}

static void* calloc_line(int x,int y,int line,int file){
 printf("Calloc called on line %d in file %d\n",line,file);
 return calloc(x,y);
}
# 28 "source/main.h"
extern unsigned char* registerList;

extern int IME;

extern int shouldDumpState;

extern unsigned int screenRefreshCount;

typedef struct PCRecall_t{
 int pc;
 int instruction;

 struct PCRecall_t* n;
} PCRecall;


PCRecall** PCRecallHead;

void dumpMemToFile(char* filename);
void dumpRegToFile(char* filename);

int runCPUCycle();

void PCRecallAdd(PCRecall** first,short pc);
PCRecall* getPCRecall(PCRecall** first,int index);
void printPCRecall(PCRecall** first,int num);
PCRecall* initPCRecall();
# 9 "source/video.c" 2
# 1 "source/instructions.h" 1







void instruction00 ();
void instruction01 ();
void instruction02 ();
void instruction03 ();
void instruction04 ();
void instruction05 ();
void instruction06 ();
void instruction07 ();
void instruction08 ();
void instruction09 ();
void instruction0A ();
void instruction0B ();
void instruction0C ();
void instruction0D ();
void instruction0E ();
void instruction0F ();
void instruction10 ();
void instruction11 ();
void instruction12 ();
void instruction13 ();
void instruction14 ();
void instruction15 ();
void instruction16 ();
void instruction17 ();
void instruction18 ();
void instruction19 ();
void instruction1A ();
void instruction1B ();
void instruction1C ();
void instruction1D ();
void instruction1E ();
void instruction1F ();
void instruction20 ();
void instruction21 ();
void instruction22 ();
void instruction23 ();
void instruction24 ();
void instruction25 ();
void instruction26 ();
void instruction27 ();
void instruction28 ();
void instruction29 ();
void instruction2A ();
void instruction2B ();
void instruction2C ();
void instruction2D ();
void instruction2E ();
void instruction2F ();
void instruction30 ();
void instruction31 ();
void instruction32 ();
void instruction33 ();
void instruction34 ();
void instruction35 ();
void instruction36 ();
void instruction37 ();
void instruction38 ();
void instruction39 ();
void instruction3A ();
void instruction3B ();
void instruction3C ();
void instruction3D ();
void instruction3E ();
void instruction3F ();
void instruction40 ();
void instruction41 ();
void instruction42 ();
void instruction43 ();
void instruction44 ();
void instruction45 ();
void instruction46 ();
void instruction47 ();
void instruction48 ();
void instruction49 ();
void instruction4A ();
void instruction4B ();
void instruction4C ();
void instruction4D ();
void instruction4E ();
void instruction4F ();

void instruction50 ();
void instruction51 ();
void instruction52 ();
void instruction53 ();
void instruction54 ();
void instruction55 ();
void instruction56 ();
void instruction57 ();
void instruction58 ();
void instruction59 ();
void instruction5A ();
void instruction5B ();
void instruction5C ();
void instruction5D ();
void instruction5E ();
void instruction5F ();

void instruction60 ();
void instruction61 ();
void instruction62 ();
void instruction63 ();
void instruction64 ();
void instruction65 ();
void instruction66 ();
void instruction67 ();
void instruction68 ();
void instruction69 ();
void instruction6A ();
void instruction6B ();
void instruction6C ();
void instruction6D ();
void instruction6E ();
void instruction6F ();

void instruction70 ();
void instruction71 ();
void instruction72 ();
void instruction73 ();
void instruction74 ();
void instruction75 ();
void instruction76 ();
void instruction77 ();
void instruction78 ();
void instruction79 ();
void instruction7A ();
void instruction7B ();
void instruction7C ();
void instruction7D ();
void instruction7E ();
void instruction7F ();

void instruction80 ();
void instruction81 ();
void instruction82 ();
void instruction83 ();
void instruction84 ();
void instruction85 ();
void instruction86 ();
void instruction87 ();
void instruction88 ();
void instruction89 ();
void instruction8A ();
void instruction8B ();
void instruction8C ();
void instruction8D ();
void instruction8E ();
void instruction8F ();
void instruction90 ();
void instruction91 ();
void instruction92 ();
void instruction93 ();
void instruction94 ();
void instruction95 ();
void instruction96 ();
void instruction97 ();
void instruction98 ();
void instruction99 ();
void instruction9A ();
void instruction9B ();
void instruction9C ();
void instruction9D ();
void instruction9E ();
void instruction9F ();
void instructionA0 ();
void instructionA1 ();
void instructionA2 ();
void instructionA3 ();
void instructionA4 ();
void instructionA5 ();
void instructionA6 ();
void instructionA7 ();
void instructionA8 ();
void instructionA9 ();
void instructionAA ();
void instructionAB ();
void instructionAC ();
void instructionAD ();
void instructionAE ();
void instructionAF ();
void instructionB0 ();
void instructionB1 ();
void instructionB2 ();
void instructionB3 ();
void instructionB4 ();
void instructionB5 ();
void instructionB6 ();
void instructionB7 ();
void instructionB8 ();
void instructionB9 ();
void instructionBA ();
void instructionBB ();
void instructionBC ();
void instructionBD ();
void instructionBE ();
void instructionBF ();
void instructionC0 ();
void instructionC1 ();
void instructionC2 ();
void instructionC3 ();
void instructionC4 ();
void instructionC5 ();
void instructionC6 ();
void instructionC7 ();
void instructionC8 ();
void instructionC9 ();
void instructionCA ();
void instructionCB ();
void instructionCC ();
void instructionCD ();
void instructionCE ();
void instructionCF ();
void instructionD0 ();
void instructionD1 ();
void instructionD2 ();

void instructionD4 ();
void instructionD5 ();
void instructionD6 ();
void instructionD7 ();
void instructionD8 ();
void instructionD9 ();
void instructionDA ();

void instructionDC ();

void instructionDE ();
void instructionDF ();
void instructionE0 ();
void instructionE1 ();
void instructionE2 ();


void instructionE5 ();
void instructionE6 ();
void instructionE7 ();
void instructionE8 ();
void instructionE9 ();
void instructionEA ();



void instructionEE ();
void instructionEF ();
void instructionF0 ();
void instructionF1 ();
void instructionF2 ();
void instructionF3 ();

void instructionF5 ();
void instructionF6 ();
void instructionF7 ();
void instructionF8 ();
void instructionF9 ();
void instructionFA ();
void instructionFB ();


void instructionFE ();
void instructionFF ();





void instructionCB00 ();
void instructionCB01 ();
void instructionCB02 ();
void instructionCB03 ();
void instructionCB04 ();
void instructionCB05 ();
void instructionCB06 ();
void instructionCB07 ();
void instructionCB08 ();
void instructionCB09 ();
void instructionCB0A ();
void instructionCB0B ();
void instructionCB0C ();
void instructionCB0D ();
void instructionCB0E ();
void instructionCB0F ();
void instructionCB10 ();
void instructionCB11 ();
void instructionCB12 ();
void instructionCB13 ();
void instructionCB14 ();
void instructionCB15 ();
void instructionCB16 ();
void instructionCB17 ();
void instructionCB18 ();
void instructionCB19 ();
void instructionCB1A ();
void instructionCB1B ();
void instructionCB1C ();
void instructionCB1D ();
void instructionCB1E ();
void instructionCB1F ();
void instructionCB20 ();
void instructionCB21 ();
void instructionCB22 ();
void instructionCB23 ();
void instructionCB24 ();
void instructionCB25 ();
void instructionCB26 ();
void instructionCB27 ();
void instructionCB28 ();
void instructionCB29 ();
void instructionCB2A ();
void instructionCB2B ();
void instructionCB2C ();
void instructionCB2D ();
void instructionCB2E ();
void instructionCB2F ();
void instructionCB30 ();
void instructionCB31 ();
void instructionCB32 ();
void instructionCB33 ();
void instructionCB34 ();
void instructionCB35 ();
void instructionCB36 ();
void instructionCB37 ();
void instructionCB38 ();
void instructionCB39 ();
void instructionCB3A ();
void instructionCB3B ();
void instructionCB3C ();
void instructionCB3D ();
void instructionCB3E ();
void instructionCB3F ();
void instructionCB40 ();
void instructionCB41 ();
void instructionCB42 ();
void instructionCB43 ();
void instructionCB44 ();
void instructionCB45 ();
void instructionCB46 ();
void instructionCB47 ();
void instructionCB48 ();
void instructionCB49 ();
void instructionCB4A ();
void instructionCB4B ();
void instructionCB4C ();
void instructionCB4D ();
void instructionCB4E ();
void instructionCB4F ();
void instructionCB50 ();
void instructionCB51 ();
void instructionCB52 ();
void instructionCB53 ();
void instructionCB54 ();
void instructionCB55 ();
void instructionCB56 ();
void instructionCB57 ();
void instructionCB58 ();
void instructionCB59 ();
void instructionCB5A ();
void instructionCB5B ();
void instructionCB5C ();
void instructionCB5D ();
void instructionCB5E ();
void instructionCB5F ();
void instructionCB60 ();
void instructionCB61 ();
void instructionCB62 ();
void instructionCB63 ();
void instructionCB64 ();
void instructionCB65 ();
void instructionCB66 ();
void instructionCB67 ();
void instructionCB68 ();
void instructionCB69 ();
void instructionCB6A ();
void instructionCB6B ();
void instructionCB6C ();
void instructionCB6D ();
void instructionCB6E ();
void instructionCB6F ();
void instructionCB70 ();
void instructionCB71 ();
void instructionCB72 ();
void instructionCB73 ();
void instructionCB74 ();
void instructionCB75 ();
void instructionCB76 ();
void instructionCB77 ();
void instructionCB78 ();
void instructionCB79 ();
void instructionCB7A ();
void instructionCB7B ();
void instructionCB7C ();
void instructionCB7D ();
void instructionCB7E ();
void instructionCB7F ();
void instructionCB80 ();
void instructionCB81 ();
void instructionCB82 ();
void instructionCB83 ();
void instructionCB84 ();
void instructionCB85 ();
void instructionCB86 ();
void instructionCB87 ();
void instructionCB88 ();
void instructionCB89 ();
void instructionCB8A ();
void instructionCB8B ();
void instructionCB8C ();
void instructionCB8D ();
void instructionCB8E ();
void instructionCB8F ();
void instructionCB90 ();
void instructionCB91 ();
void instructionCB92 ();
void instructionCB93 ();
void instructionCB94 ();
void instructionCB95 ();
void instructionCB96 ();
void instructionCB97 ();
void instructionCB98 ();
void instructionCB99 ();
void instructionCB9A ();
void instructionCB9B ();
void instructionCB9C ();
void instructionCB9D ();
void instructionCB9E ();
void instructionCB9F ();
void instructionCBA0 ();
void instructionCBA1 ();
void instructionCBA2 ();
void instructionCBA3 ();
void instructionCBA4 ();
void instructionCBA5 ();
void instructionCBA6 ();
void instructionCBA7 ();
void instructionCBA8 ();
void instructionCBA9 ();
void instructionCBAA ();
void instructionCBAB ();
void instructionCBAC ();
void instructionCBAD ();
void instructionCBAE ();
void instructionCBAF ();
void instructionCBB0 ();
void instructionCBB1 ();
void instructionCBB2 ();
void instructionCBB3 ();
void instructionCBB4 ();
void instructionCBB5 ();
void instructionCBB6 ();
void instructionCBB7 ();
void instructionCBB8 ();
void instructionCBB9 ();
void instructionCBBA ();
void instructionCBBB ();
void instructionCBBC ();
void instructionCBBD ();
void instructionCBBE ();
void instructionCBBF ();
void instructionCBC0 ();
void instructionCBC1 ();
void instructionCBC2 ();
void instructionCBC3 ();
void instructionCBC4 ();
void instructionCBC5 ();
void instructionCBC6 ();
void instructionCBC7 ();
void instructionCBC8 ();
void instructionCBC9 ();
void instructionCBCA ();
void instructionCBCB ();
void instructionCBCC ();
void instructionCBCD ();
void instructionCBCE ();
void instructionCBCF ();
void instructionCBD0 ();
void instructionCBD1 ();
void instructionCBD2 ();
void instructionCBD3 ();
void instructionCBD4 ();
void instructionCBD5 ();
void instructionCBD6 ();
void instructionCBD7 ();
void instructionCBD8 ();
void instructionCBD9 ();
void instructionCBDA ();
void instructionCBDB ();
void instructionCBDC ();
void instructionCBDD ();
void instructionCBDE ();
void instructionCBDF ();
void instructionCBE0 ();
void instructionCBE1 ();
void instructionCBE2 ();
void instructionCBE3 ();
void instructionCBE4 ();
void instructionCBE5 ();
void instructionCBE6 ();
void instructionCBE7 ();
void instructionCBE8 ();
void instructionCBE9 ();
void instructionCBEA ();
void instructionCBEB ();
void instructionCBEC ();
void instructionCBED ();
void instructionCBEE ();
void instructionCBEF ();
void instructionCBF0 ();
void instructionCBF1 ();
void instructionCBF2 ();
void instructionCBF3 ();
void instructionCBF4 ();
void instructionCBF5 ();
void instructionCBF6 ();
void instructionCBF7 ();
void instructionCBF8 ();
void instructionCBF9 ();
void instructionCBFA ();
void instructionCBFB ();
void instructionCBFC ();
void instructionCBFD ();
void instructionCBFE ();
void instructionCBFF ();
# 10 "source/video.c" 2
# 1 "source/core.h" 1
# 10 "source/core.h"
typedef void (*opcodeInstruction)();

extern unsigned char* registerList;
extern opcodeInstruction* opcodes;
int delayCyclesLeft;

void setInterrupt(char a);
void clearInterrupt(char a);

void writeAF(short value);
void writeBC(short value);
void writeDE(short value);
void writeHL(short value);
void writeSP(short value);
void writePC(short value);

void writeA(char value);
void writeF(char value);
void writeB(char value);
void writeC(char value);
void writeD(char value);
void writeE(char value);
void writeH(char value);
void writeL(char value);

unsigned short getAF();
unsigned short getBC();
unsigned short getDE();
unsigned short getHL();
unsigned short getSP();
unsigned short getPC();

unsigned char getA();
unsigned char getF();
unsigned char getB();
unsigned char getC();
unsigned char getD();
unsigned char getE();
unsigned char getH();
unsigned char getL();

void setFlagZ();
void setFlagN();
void setFlagH();
void setFlagC();

void clearFlagZ();
void clearFlagN();
void clearFlagH();
void clearFlagC();

int getFlagZ();
int getFlagN();
int getFlagH();
int getFlagC();

short signedAdd(short num1,char num2);

int runCPUCycle();
# 11 "source/video.c" 2
# 1 "source/mem.h" 1



extern unsigned char* romBanks;
extern unsigned char* vramBanks;
extern unsigned char* ramBanks;
extern unsigned char* workBanks;
extern unsigned char* OAMTable;
extern unsigned char* IOPorts;
extern unsigned char* hram;
extern unsigned char interruptER;

extern int currentRomBank;
extern int currentVramBank;
extern int currentRamBank;
extern int currentWorkBank;

void initMem(int numMemBanks,int ramSize,char cartType);

int writeCharToMem(int loc,char value);
int writeShortToMem(int loc,short value);

unsigned short readShortFromMem(int loc);
unsigned char readCharFromMem(int loc);

unsigned short changeEndian(short num);
# 12 "source/video.c" 2
# 1 "source/video.h" 1



int spriteTableChanged;

void initVideo();
void updateVideo(int screenRefreshCount);
# 13 "source/video.c" 2
# 1 "source/io.h" 1
# 11 "source/io.h"
unsigned char getLCDControl (); unsigned char setLCDControl ();
unsigned char getLCDStatus (); unsigned char setLCDStatus ();
unsigned char getscrollY (); unsigned char setscrollY ();
unsigned char getscrollX (); unsigned char setscrollX ();
unsigned char getLY (); unsigned char setLY ();
unsigned char getLYC (); unsigned char setLYC ();
unsigned char getWY (); unsigned char setWY ();
unsigned char getWX (); unsigned char setWX ();

unsigned char getBGPaletteData (); unsigned char setBGPaletteData ();
unsigned char getobj0Palette (); unsigned char setobj0Palette ();
unsigned char getobj1Palette (); unsigned char setobj1Palette ();

unsigned char getBGPaletteIndex (); unsigned char setBGPaletteIndex ();
unsigned char getBGPaletteDataCGB (); unsigned char setBGPaletteDataCGB ();
unsigned char getspritePaletteIndex (); unsigned char setspritePaletteIndex ();
unsigned char getspritePaletteData (); unsigned char setspritePaletteData ();






unsigned char getVRAMBank (); unsigned char setVRAMBank ();
unsigned char getDMATransfer (); unsigned char setDMATransfer ();

unsigned char getDMASourceHigh (); unsigned char setDMASourceHigh ();
unsigned char getDMASourceLow (); unsigned char setDMASourceLow ();
unsigned char getDMADestHigh (); unsigned char setDMADestHigh ();
unsigned char getDMADestLow (); unsigned char setDMADestLow ();
unsigned char getDMAVRAMStart (); unsigned char setDMAVRAMStart ();




unsigned char getch1Sweep (); unsigned char setch1Sweep ();
unsigned char getch1Length (); unsigned char setch1Length ();
unsigned char getch1VolumeEnv (); unsigned char setch1VolumeEnv ();
unsigned char getch1FreqLow (); unsigned char setch1FreqLow ();
unsigned char getch1FreqHigh (); unsigned char setch1FreqHigh ();

unsigned char getch2Length (); unsigned char setch2Length ();
unsigned char getch2VolumeEnv (); unsigned char setch2VolumeEnv ();
unsigned char getch2FreqLow (); unsigned char setch2FreqLow ();
unsigned char getch2FreqHigh (); unsigned char setch2FreqHigh ();

unsigned char getch3On (); unsigned char setch3On ();
unsigned char getch3Length (); unsigned char setch3Length ();
unsigned char getch3Level (); unsigned char setch3Level ();
unsigned char getch3FreqLow (); unsigned char setch3FreqLow ();
unsigned char getch3FreqHigh (); unsigned char setch3FreqHigh ();
unsigned char getch3WaveRAM (); unsigned char setch3WaveRAM ();

unsigned char getch4Length (); unsigned char setch4Length ();
unsigned char getch4VolumeEnv (); unsigned char setch4VolumeEnv ();
unsigned char getch4PolyCounter (); unsigned char setch4PolyCounter ();
unsigned char getch4Counter (); unsigned char setch4Counter ();

unsigned char getchannelControl (); unsigned char setchannelControl ();
unsigned char getsoundOutput (); unsigned char setsoundOutput ();
unsigned char getsoundON (); unsigned char setsoundON ();





unsigned char getjoypadRead (); unsigned char setjoypadRead ();





unsigned char getserialData (); unsigned char setserialData ();
unsigned char getserialControl (); unsigned char setserialControl ();





unsigned char getdivRegister (); unsigned char setdivRegister ();
unsigned char gettimerCounter (); unsigned char settimerCounter ();
unsigned char gettimerModulo (); unsigned char settimerModulo ();
unsigned char gettimerControl (); unsigned char settimerControl ();

unsigned char getinterruptFlags (); unsigned char setinterruptFlags ();





unsigned char getspeedSwitch (); unsigned char setspeedSwitch ();
unsigned char getIRPort (); unsigned char setIRPort ();
unsigned char getWRAMBank (); unsigned char setWRAMBank ();

extern signed int lastAddrWritten;


void initIO();
void writeIO(int loc,char value);
char readIO(int loc);
int checkPermissions(int port);
# 14 "source/video.c" 2
# 1 "source/dma.h" 1



int isOAMDMAActive();
void runOAMDMA();
void startOAMDMA(char value);
# 15 "source/video.c" 2
# 1 "source/joypad.h" 1






extern int buttonMatrix;
extern int currentButtonSelect;

void initJoypad();
void joypadUpdate();
# 16 "source/video.c" 2
# 1 "source/SDL_rotozoom.h" 1
# 33 "source/SDL_rotozoom.h"
# 1 "/usr/include/math.h" 1 3 4
# 28 "/usr/include/math.h" 3 4




# 1 "/usr/include/bits/huge_val.h" 1 3 4
# 33 "/usr/include/math.h" 2 3 4

# 1 "/usr/include/bits/huge_valf.h" 1 3 4
# 35 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/huge_vall.h" 1 3 4
# 36 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/inf.h" 1 3 4
# 39 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/nan.h" 1 3 4
# 42 "/usr/include/math.h" 2 3 4



# 1 "/usr/include/bits/mathdef.h" 1 3 4
# 28 "/usr/include/bits/mathdef.h" 3 4
typedef float float_t;
typedef double double_t;
# 46 "/usr/include/math.h" 2 3 4
# 69 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));







extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));








extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));





extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));






extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));








extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));





extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));






extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));






extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));





extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));






extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
# 70 "/usr/include/math.h" 2 3 4
# 88 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));







extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));








extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));





extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));






extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));








extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));





extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));






extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));






extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));





extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));






extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));
# 89 "/usr/include/math.h" 2 3 4
# 132 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));







extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));








extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));






extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));








extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
# 133 "/usr/include/math.h" 2 3 4
# 148 "/usr/include/math.h" 3 4
extern int signgam;
# 189 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN =

      0,
    FP_INFINITE =

      1,
    FP_ZERO =

      2,
    FP_SUBNORMAL =

      3,
    FP_NORMAL =

      4
  };
# 301 "/usr/include/math.h" 3 4
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;




extern _LIB_VERSION_TYPE _LIB_VERSION;
# 326 "/usr/include/math.h" 3 4
struct exception

  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




extern int matherr (struct exception *__exc);
# 488 "/usr/include/math.h" 3 4

# 34 "source/SDL_rotozoom.h" 2
# 44 "source/SDL_rotozoom.h"
# 1 "/usr/local/include/SDL/SDL.h" 1 3
# 30 "/usr/local/include/SDL/SDL.h" 3
# 1 "/usr/local/include/SDL/SDL_main.h" 1 3
# 26 "/usr/local/include/SDL/SDL_main.h" 3
# 1 "/usr/local/include/SDL/SDL_stdinc.h" 1 3
# 30 "/usr/local/include/SDL/SDL_stdinc.h" 3
# 1 "/usr/local/include/SDL/SDL_config.h" 1 3
# 30 "/usr/local/include/SDL/SDL_config.h" 3
# 1 "/usr/local/include/SDL/SDL_platform.h" 1 3
# 31 "/usr/local/include/SDL/SDL_config.h" 2 3
# 31 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 41 "/usr/local/include/SDL/SDL_stdinc.h" 3
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 147 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 42 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdarg.h" 1 3 4
# 43 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 60 "/usr/local/include/SDL/SDL_stdinc.h" 3
# 1 "/usr/include/string.h" 1 3 4
# 27 "/usr/include/string.h" 3 4





# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 33 "/usr/include/string.h" 2 3 4
# 44 "/usr/include/string.h" 3 4


extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 96 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 127 "/usr/include/string.h" 3 4


extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 166 "/usr/include/string.h" 3 4
extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 211 "/usr/include/string.h" 3 4

# 236 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 263 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 282 "/usr/include/string.h" 3 4



extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 315 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 342 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 397 "/usr/include/string.h" 3 4


extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

# 427 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)));
# 445 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 489 "/usr/include/string.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 517 "/usr/include/string.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 534 "/usr/include/string.h" 3 4
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 557 "/usr/include/string.h" 3 4
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 644 "/usr/include/string.h" 3 4

# 61 "/usr/local/include/SDL/SDL_stdinc.h" 2 3


# 1 "/usr/include/strings.h" 1 3 4
# 64 "/usr/local/include/SDL/SDL_stdinc.h" 2 3


# 1 "/usr/include/inttypes.h" 1 3 4
# 27 "/usr/include/inttypes.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/wchar.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/stdint.h" 2 3 4
# 48 "/usr/include/stdint.h" 3 4
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;



typedef unsigned long int uint64_t;
# 65 "/usr/include/stdint.h" 3 4
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
# 90 "/usr/include/stdint.h" 3 4
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 103 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 119 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 134 "/usr/include/stdint.h" 3 4
typedef long int intmax_t;
typedef unsigned long int uintmax_t;
# 10 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stdint.h" 2 3 4
# 28 "/usr/include/inttypes.h" 2 3 4






typedef int __gwchar_t;
# 266 "/usr/include/inttypes.h" 3 4





typedef struct
  {
    long int quot;
    long int rem;
  } imaxdiv_t;
# 290 "/usr/include/inttypes.h" 3 4
extern intmax_t imaxabs (intmax_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern imaxdiv_t imaxdiv (intmax_t __numer, intmax_t __denom)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern intmax_t strtoimax (const char *__restrict __nptr,
      char **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t strtoumax (const char *__restrict __nptr,
       char ** __restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));


extern intmax_t wcstoimax (const __gwchar_t *__restrict __nptr,
      __gwchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));


extern uintmax_t wcstoumax (const __gwchar_t *__restrict __nptr,
       __gwchar_t ** __restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));
# 432 "/usr/include/inttypes.h" 3 4

# 67 "/usr/local/include/SDL/SDL_stdinc.h" 2 3




# 1 "/usr/include/ctype.h" 1 3 4
# 28 "/usr/include/ctype.h" 3 4

# 46 "/usr/include/ctype.h" 3 4
enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
# 79 "/usr/include/ctype.h" 3 4
extern const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 104 "/usr/include/ctype.h" 3 4






extern int isalnum (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha (int) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int islower (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint (int) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit (int) __attribute__ ((__nothrow__ , __leaf__));



extern int tolower (int __c) __attribute__ ((__nothrow__ , __leaf__));


extern int toupper (int __c) __attribute__ ((__nothrow__ , __leaf__));








extern int isblank (int) __attribute__ ((__nothrow__ , __leaf__));


# 150 "/usr/include/ctype.h" 3 4
extern int isascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int toascii (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int _toupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int _tolower (int) __attribute__ ((__nothrow__ , __leaf__));
# 271 "/usr/include/ctype.h" 3 4
extern int isalnum_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int islower_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));

extern int isblank_l (int, __locale_t) __attribute__ ((__nothrow__ , __leaf__));



extern int __tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int tolower_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));


extern int __toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
extern int toupper_l (int __c, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));
# 347 "/usr/include/ctype.h" 3 4

# 72 "/usr/local/include/SDL/SDL_stdinc.h" 2 3


# 1 "/usr/include/iconv.h" 1 3 4
# 23 "/usr/include/iconv.h" 3 4
# 1 "/usr/lib/gcc/x86_64-unknown-linux-gnu/4.8.2/include/stddef.h" 1 3 4
# 24 "/usr/include/iconv.h" 2 3 4





typedef void *iconv_t;







extern iconv_t iconv_open (const char *__tocode, const char *__fromcode);




extern size_t iconv (iconv_t __cd, char **__restrict __inbuf,
       size_t *__restrict __inbytesleft,
       char **__restrict __outbuf,
       size_t *__restrict __outbytesleft);





extern int iconv_close (iconv_t __cd);


# 75 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 93 "/usr/local/include/SDL/SDL_stdinc.h" 3
typedef enum {
 SDL_FALSE = 0,
 SDL_TRUE = 1
} SDL_bool;

typedef int8_t Sint8;
typedef uint8_t Uint8;
typedef int16_t Sint16;
typedef uint16_t Uint16;
typedef int32_t Sint32;
typedef uint32_t Uint32;


typedef int64_t Sint64;

typedef uint64_t Uint64;
# 125 "/usr/local/include/SDL/SDL_stdinc.h" 3
typedef int SDL_dummy_uint8[(sizeof(Uint8) == 1) * 2 - 1];
typedef int SDL_dummy_sint8[(sizeof(Sint8) == 1) * 2 - 1];
typedef int SDL_dummy_uint16[(sizeof(Uint16) == 2) * 2 - 1];
typedef int SDL_dummy_sint16[(sizeof(Sint16) == 2) * 2 - 1];
typedef int SDL_dummy_uint32[(sizeof(Uint32) == 4) * 2 - 1];
typedef int SDL_dummy_sint32[(sizeof(Sint32) == 4) * 2 - 1];
typedef int SDL_dummy_uint64[(sizeof(Uint64) == 8) * 2 - 1];
typedef int SDL_dummy_sint64[(sizeof(Sint64) == 8) * 2 - 1];
# 146 "/usr/local/include/SDL/SDL_stdinc.h" 3
typedef enum {
 DUMMY_ENUM_VALUE
} SDL_DUMMY_ENUM;


typedef int SDL_dummy_enum[(sizeof(SDL_DUMMY_ENUM) == sizeof(int)) * 2 - 1];



# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 156 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 370 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) void * SDL_revcpy(void *dst, const void *src, size_t len);
# 403 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) size_t SDL_strlcpy(char *dst, const char *src, size_t maxlen);





extern __attribute__ ((visibility("default"))) size_t SDL_strlcat(char *dst, const char *src, size_t maxlen);
# 421 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) char * SDL_strrev(char *string);





extern __attribute__ ((visibility("default"))) char * SDL_strupr(char *string);





extern __attribute__ ((visibility("default"))) char * SDL_strlwr(char *string);
# 467 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) char * SDL_ltoa(long value, char *string, int radix);
# 479 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) char * SDL_ultoa(unsigned long value, char *string, int radix);
# 499 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) char* SDL_lltoa(Sint64 value, char *string, int radix);





extern __attribute__ ((visibility("default"))) char* SDL_ulltoa(Uint64 value, char *string, int radix);
# 605 "/usr/local/include/SDL/SDL_stdinc.h" 3
extern __attribute__ ((visibility("default"))) size_t SDL_iconv(iconv_t cd, const char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft);



extern __attribute__ ((visibility("default"))) char * SDL_iconv_string(const char *tocode, const char *fromcode, const char *inbuf, size_t inbytesleft);
# 618 "/usr/local/include/SDL/SDL_stdinc.h" 3
# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 619 "/usr/local/include/SDL/SDL_stdinc.h" 2 3
# 27 "/usr/local/include/SDL/SDL_main.h" 2 3
# 31 "/usr/local/include/SDL/SDL.h" 2 3

# 1 "/usr/local/include/SDL/SDL_audio.h" 1 3
# 32 "/usr/local/include/SDL/SDL_audio.h" 3
# 1 "/usr/local/include/SDL/SDL_error.h" 1 3
# 33 "/usr/local/include/SDL/SDL_error.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 34 "/usr/local/include/SDL/SDL_error.h" 2 3
# 43 "/usr/local/include/SDL/SDL_error.h" 3
extern __attribute__ ((visibility("default"))) void SDL_SetError(const char *fmt, ...);
extern __attribute__ ((visibility("default"))) char * SDL_GetError(void);
extern __attribute__ ((visibility("default"))) void SDL_ClearError(void);
# 55 "/usr/local/include/SDL/SDL_error.h" 3
typedef enum {
 SDL_ENOMEM,
 SDL_EFREAD,
 SDL_EFWRITE,
 SDL_EFSEEK,
 SDL_UNSUPPORTED,
 SDL_LASTERROR
} SDL_errorcode;
extern __attribute__ ((visibility("default"))) void SDL_Error(SDL_errorcode code);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 71 "/usr/local/include/SDL/SDL_error.h" 2 3
# 33 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 1 "/usr/local/include/SDL/SDL_endian.h" 1 3
# 59 "/usr/local/include/SDL/SDL_endian.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 60 "/usr/local/include/SDL/SDL_endian.h" 2 3
# 81 "/usr/local/include/SDL/SDL_endian.h" 3
static __inline__ Uint16 SDL_Swap16(Uint16 x)
{
 __asm__("xchgb %b0,%h0" : "=Q" (x) : "0" (x));
 return x;
}
# 114 "/usr/local/include/SDL/SDL_endian.h" 3
static __inline__ Uint32 SDL_Swap32(Uint32 x)
{
 __asm__("bswapl %0" : "=r" (x) : "0" (x));
 return x;
}
# 157 "/usr/local/include/SDL/SDL_endian.h" 3
static __inline__ Uint64 SDL_Swap64(Uint64 x)
{
 __asm__("bswapq %0" : "=r" (x) : "0" (x));
 return x;
}
# 212 "/usr/local/include/SDL/SDL_endian.h" 3
# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 213 "/usr/local/include/SDL/SDL_endian.h" 2 3
# 34 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 1 "/usr/local/include/SDL/SDL_mutex.h" 1 3
# 35 "/usr/local/include/SDL/SDL_mutex.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 36 "/usr/local/include/SDL/SDL_mutex.h" 2 3
# 55 "/usr/local/include/SDL/SDL_mutex.h" 3
struct SDL_mutex;
typedef struct SDL_mutex SDL_mutex;


extern __attribute__ ((visibility("default"))) SDL_mutex * SDL_CreateMutex(void);





extern __attribute__ ((visibility("default"))) int SDL_mutexP(SDL_mutex *mutex);
# 74 "/usr/local/include/SDL/SDL_mutex.h" 3
extern __attribute__ ((visibility("default"))) int SDL_mutexV(SDL_mutex *mutex);


extern __attribute__ ((visibility("default"))) void SDL_DestroyMutex(SDL_mutex *mutex);
# 86 "/usr/local/include/SDL/SDL_mutex.h" 3
struct SDL_semaphore;
typedef struct SDL_semaphore SDL_sem;


extern __attribute__ ((visibility("default"))) SDL_sem * SDL_CreateSemaphore(Uint32 initial_value);


extern __attribute__ ((visibility("default"))) void SDL_DestroySemaphore(SDL_sem *sem);






extern __attribute__ ((visibility("default"))) int SDL_SemWait(SDL_sem *sem);





extern __attribute__ ((visibility("default"))) int SDL_SemTryWait(SDL_sem *sem);
# 115 "/usr/local/include/SDL/SDL_mutex.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 ms);




extern __attribute__ ((visibility("default"))) int SDL_SemPost(SDL_sem *sem);


extern __attribute__ ((visibility("default"))) Uint32 SDL_SemValue(SDL_sem *sem);
# 133 "/usr/local/include/SDL/SDL_mutex.h" 3
struct SDL_cond;
typedef struct SDL_cond SDL_cond;



extern __attribute__ ((visibility("default"))) SDL_cond * SDL_CreateCond(void);


extern __attribute__ ((visibility("default"))) void SDL_DestroyCond(SDL_cond *cond);




extern __attribute__ ((visibility("default"))) int SDL_CondSignal(SDL_cond *cond);




extern __attribute__ ((visibility("default"))) int SDL_CondBroadcast(SDL_cond *cond);






extern __attribute__ ((visibility("default"))) int SDL_CondWait(SDL_cond *cond, SDL_mutex *mut);







extern __attribute__ ((visibility("default"))) int SDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, Uint32 ms);







# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 175 "/usr/local/include/SDL/SDL_mutex.h" 2 3
# 35 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 1 "/usr/local/include/SDL/SDL_thread.h" 1 3
# 38 "/usr/local/include/SDL/SDL_thread.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 39 "/usr/local/include/SDL/SDL_thread.h" 2 3






struct SDL_Thread;
typedef struct SDL_Thread SDL_Thread;
# 88 "/usr/local/include/SDL/SDL_thread.h" 3
extern __attribute__ ((visibility("default"))) SDL_Thread * SDL_CreateThread(int ( *fn)(void *), void *data);



extern __attribute__ ((visibility("default"))) Uint32 SDL_ThreadID(void);




extern __attribute__ ((visibility("default"))) Uint32 SDL_GetThreadID(SDL_Thread *thread);





extern __attribute__ ((visibility("default"))) void SDL_WaitThread(SDL_Thread *thread, int *status);


extern __attribute__ ((visibility("default"))) void SDL_KillThread(SDL_Thread *thread);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 114 "/usr/local/include/SDL/SDL_thread.h" 2 3
# 36 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 1 "/usr/local/include/SDL/SDL_rwops.h" 1 3
# 34 "/usr/local/include/SDL/SDL_rwops.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_rwops.h" 2 3







typedef struct SDL_RWops {




 int ( *seek)(struct SDL_RWops *context, int offset, int whence);





 int ( *read)(struct SDL_RWops *context, void *ptr, int size, int maxnum);





 int ( *write)(struct SDL_RWops *context, const void *ptr, int size, int num);


 int ( *close)(struct SDL_RWops *context);

 Uint32 type;
 union {
# 78 "/usr/local/include/SDL/SDL_rwops.h" 3
     struct {
  int autoclose;
   FILE *fp;
     } stdio;

     struct {
  Uint8 *base;
   Uint8 *here;
  Uint8 *stop;
     } mem;
     struct {
  void *data1;
     } unknown;
 } hidden;

} SDL_RWops;





extern __attribute__ ((visibility("default"))) SDL_RWops * SDL_RWFromFile(const char *file, const char *mode);


extern __attribute__ ((visibility("default"))) SDL_RWops * SDL_RWFromFP(FILE *fp, int autoclose);


extern __attribute__ ((visibility("default"))) SDL_RWops * SDL_RWFromMem(void *mem, int size);
extern __attribute__ ((visibility("default"))) SDL_RWops * SDL_RWFromConstMem(const void *mem, int size);

extern __attribute__ ((visibility("default"))) SDL_RWops * SDL_AllocRW(void);
extern __attribute__ ((visibility("default"))) void SDL_FreeRW(SDL_RWops *area);
# 131 "/usr/local/include/SDL/SDL_rwops.h" 3
extern __attribute__ ((visibility("default"))) Uint16 SDL_ReadLE16(SDL_RWops *src);
extern __attribute__ ((visibility("default"))) Uint16 SDL_ReadBE16(SDL_RWops *src);
extern __attribute__ ((visibility("default"))) Uint32 SDL_ReadLE32(SDL_RWops *src);
extern __attribute__ ((visibility("default"))) Uint32 SDL_ReadBE32(SDL_RWops *src);
extern __attribute__ ((visibility("default"))) Uint64 SDL_ReadLE64(SDL_RWops *src);
extern __attribute__ ((visibility("default"))) Uint64 SDL_ReadBE64(SDL_RWops *src);




extern __attribute__ ((visibility("default"))) int SDL_WriteLE16(SDL_RWops *dst, Uint16 value);
extern __attribute__ ((visibility("default"))) int SDL_WriteBE16(SDL_RWops *dst, Uint16 value);
extern __attribute__ ((visibility("default"))) int SDL_WriteLE32(SDL_RWops *dst, Uint32 value);
extern __attribute__ ((visibility("default"))) int SDL_WriteBE32(SDL_RWops *dst, Uint32 value);
extern __attribute__ ((visibility("default"))) int SDL_WriteLE64(SDL_RWops *dst, Uint64 value);
extern __attribute__ ((visibility("default"))) int SDL_WriteBE64(SDL_RWops *dst, Uint64 value);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 154 "/usr/local/include/SDL/SDL_rwops.h" 2 3
# 37 "/usr/local/include/SDL/SDL_audio.h" 2 3

# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 39 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 74 "/usr/local/include/SDL/SDL_audio.h" 3
typedef struct SDL_AudioSpec {
 int freq;
 Uint16 format;
 Uint8 channels;
 Uint8 silence;
 Uint16 samples;
 Uint16 padding;
 Uint32 size;
# 91 "/usr/local/include/SDL/SDL_audio.h" 3
 void ( *callback)(void *userdata, Uint8 *stream, int len);
 void *userdata;
} SDL_AudioSpec;
# 126 "/usr/local/include/SDL/SDL_audio.h" 3
typedef struct SDL_AudioCVT {
 int needed;
 Uint16 src_format;
 Uint16 dst_format;
 double rate_incr;
 Uint8 *buf;
 int len;
 int len_cvt;
 int len_mult;
 double len_ratio;
 void ( *filters[10])(struct SDL_AudioCVT *cvt, Uint16 format);
 int filter_index;
} SDL_AudioCVT;
# 150 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) int SDL_AudioInit(const char *driver_name);
extern __attribute__ ((visibility("default"))) void SDL_AudioQuit(void);







extern __attribute__ ((visibility("default"))) char * SDL_AudioDriverName(char *namebuf, int maxlen);
# 178 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained);

typedef enum {
 SDL_AUDIO_STOPPED = 0,
 SDL_AUDIO_PLAYING,
 SDL_AUDIO_PAUSED
} SDL_audiostatus;


extern __attribute__ ((visibility("default"))) SDL_audiostatus SDL_GetAudioStatus(void);
# 196 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) void SDL_PauseAudio(int pause_on);
# 215 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) SDL_AudioSpec * SDL_LoadWAV_RW(SDL_RWops *src, int freesrc, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len);
# 224 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) void SDL_FreeWAV(Uint8 *audio_buf);
# 234 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) int SDL_BuildAudioCVT(SDL_AudioCVT *cvt,
  Uint16 src_format, Uint8 src_channels, int src_rate,
  Uint16 dst_format, Uint8 dst_channels, int dst_rate);
# 247 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) int SDL_ConvertAudio(SDL_AudioCVT *cvt);
# 258 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) void SDL_MixAudio(Uint8 *dst, const Uint8 *src, Uint32 len, int volume);
# 268 "/usr/local/include/SDL/SDL_audio.h" 3
extern __attribute__ ((visibility("default"))) void SDL_LockAudio(void);
extern __attribute__ ((visibility("default"))) void SDL_UnlockAudio(void);





extern __attribute__ ((visibility("default"))) void SDL_CloseAudio(void);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 283 "/usr/local/include/SDL/SDL_audio.h" 2 3
# 33 "/usr/local/include/SDL/SDL.h" 2 3
# 1 "/usr/local/include/SDL/SDL_cdrom.h" 1 3
# 34 "/usr/local/include/SDL/SDL_cdrom.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_cdrom.h" 2 3
# 59 "/usr/local/include/SDL/SDL_cdrom.h" 3
typedef enum {
 CD_TRAYEMPTY,
 CD_STOPPED,
 CD_PLAYING,
 CD_PAUSED,
 CD_ERROR = -1
} CDstatus;




typedef struct SDL_CDtrack {
 Uint8 id;
 Uint8 type;
 Uint16 unused;
 Uint32 length;
 Uint32 offset;
} SDL_CDtrack;


typedef struct SDL_CD {
 int id;
 CDstatus status;



 int numtracks;
 int cur_track;
 int cur_frame;
 SDL_CDtrack track[99 +1];

} SDL_CD;
# 114 "/usr/local/include/SDL/SDL_cdrom.h" 3
extern __attribute__ ((visibility("default"))) int SDL_CDNumDrives(void);
# 123 "/usr/local/include/SDL/SDL_cdrom.h" 3
extern __attribute__ ((visibility("default"))) const char * SDL_CDName(int drive);
# 132 "/usr/local/include/SDL/SDL_cdrom.h" 3
extern __attribute__ ((visibility("default"))) SDL_CD * SDL_CDOpen(int drive);






extern __attribute__ ((visibility("default"))) CDstatus SDL_CDStatus(SDL_CD *cdrom);
# 163 "/usr/local/include/SDL/SDL_cdrom.h" 3
extern __attribute__ ((visibility("default"))) int SDL_CDPlayTracks(SDL_CD *cdrom,
  int start_track, int start_frame, int ntracks, int nframes);





extern __attribute__ ((visibility("default"))) int SDL_CDPlay(SDL_CD *cdrom, int start, int length);




extern __attribute__ ((visibility("default"))) int SDL_CDPause(SDL_CD *cdrom);




extern __attribute__ ((visibility("default"))) int SDL_CDResume(SDL_CD *cdrom);




extern __attribute__ ((visibility("default"))) int SDL_CDStop(SDL_CD *cdrom);




extern __attribute__ ((visibility("default"))) int SDL_CDEject(SDL_CD *cdrom);


extern __attribute__ ((visibility("default"))) void SDL_CDClose(SDL_CD *cdrom);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 201 "/usr/local/include/SDL/SDL_cdrom.h" 2 3
# 34 "/usr/local/include/SDL/SDL.h" 2 3
# 1 "/usr/local/include/SDL/SDL_cpuinfo.h" 1 3
# 33 "/usr/local/include/SDL/SDL_cpuinfo.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 34 "/usr/local/include/SDL/SDL_cpuinfo.h" 2 3






extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasRDTSC(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasMMX(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasMMXExt(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_Has3DNow(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_Has3DNowExt(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasSSE(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasSSE2(void);


extern __attribute__ ((visibility("default"))) SDL_bool SDL_HasAltiVec(void);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 68 "/usr/local/include/SDL/SDL_cpuinfo.h" 2 3
# 35 "/usr/local/include/SDL/SDL.h" 2 3


# 1 "/usr/local/include/SDL/SDL_events.h" 1 3
# 33 "/usr/local/include/SDL/SDL_events.h" 3
# 1 "/usr/local/include/SDL/SDL_active.h" 1 3
# 34 "/usr/local/include/SDL/SDL_active.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_active.h" 2 3
# 54 "/usr/local/include/SDL/SDL_active.h" 3
extern __attribute__ ((visibility("default"))) Uint8 SDL_GetAppState(void);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 62 "/usr/local/include/SDL/SDL_active.h" 2 3
# 34 "/usr/local/include/SDL/SDL_events.h" 2 3
# 1 "/usr/local/include/SDL/SDL_keyboard.h" 1 3
# 32 "/usr/local/include/SDL/SDL_keyboard.h" 3
# 1 "/usr/local/include/SDL/SDL_keysym.h" 1 3
# 31 "/usr/local/include/SDL/SDL_keysym.h" 3
typedef enum {




 SDLK_UNKNOWN = 0,
 SDLK_FIRST = 0,
 SDLK_BACKSPACE = 8,
 SDLK_TAB = 9,
 SDLK_CLEAR = 12,
 SDLK_RETURN = 13,
 SDLK_PAUSE = 19,
 SDLK_ESCAPE = 27,
 SDLK_SPACE = 32,
 SDLK_EXCLAIM = 33,
 SDLK_QUOTEDBL = 34,
 SDLK_HASH = 35,
 SDLK_DOLLAR = 36,
 SDLK_AMPERSAND = 38,
 SDLK_QUOTE = 39,
 SDLK_LEFTPAREN = 40,
 SDLK_RIGHTPAREN = 41,
 SDLK_ASTERISK = 42,
 SDLK_PLUS = 43,
 SDLK_COMMA = 44,
 SDLK_MINUS = 45,
 SDLK_PERIOD = 46,
 SDLK_SLASH = 47,
 SDLK_0 = 48,
 SDLK_1 = 49,
 SDLK_2 = 50,
 SDLK_3 = 51,
 SDLK_4 = 52,
 SDLK_5 = 53,
 SDLK_6 = 54,
 SDLK_7 = 55,
 SDLK_8 = 56,
 SDLK_9 = 57,
 SDLK_COLON = 58,
 SDLK_SEMICOLON = 59,
 SDLK_LESS = 60,
 SDLK_EQUALS = 61,
 SDLK_GREATER = 62,
 SDLK_QUESTION = 63,
 SDLK_AT = 64,



 SDLK_LEFTBRACKET = 91,
 SDLK_BACKSLASH = 92,
 SDLK_RIGHTBRACKET = 93,
 SDLK_CARET = 94,
 SDLK_UNDERSCORE = 95,
 SDLK_BACKQUOTE = 96,
 SDLK_a = 97,
 SDLK_b = 98,
 SDLK_c = 99,
 SDLK_d = 100,
 SDLK_e = 101,
 SDLK_f = 102,
 SDLK_g = 103,
 SDLK_h = 104,
 SDLK_i = 105,
 SDLK_j = 106,
 SDLK_k = 107,
 SDLK_l = 108,
 SDLK_m = 109,
 SDLK_n = 110,
 SDLK_o = 111,
 SDLK_p = 112,
 SDLK_q = 113,
 SDLK_r = 114,
 SDLK_s = 115,
 SDLK_t = 116,
 SDLK_u = 117,
 SDLK_v = 118,
 SDLK_w = 119,
 SDLK_x = 120,
 SDLK_y = 121,
 SDLK_z = 122,
 SDLK_DELETE = 127,





 SDLK_WORLD_0 = 160,
 SDLK_WORLD_1 = 161,
 SDLK_WORLD_2 = 162,
 SDLK_WORLD_3 = 163,
 SDLK_WORLD_4 = 164,
 SDLK_WORLD_5 = 165,
 SDLK_WORLD_6 = 166,
 SDLK_WORLD_7 = 167,
 SDLK_WORLD_8 = 168,
 SDLK_WORLD_9 = 169,
 SDLK_WORLD_10 = 170,
 SDLK_WORLD_11 = 171,
 SDLK_WORLD_12 = 172,
 SDLK_WORLD_13 = 173,
 SDLK_WORLD_14 = 174,
 SDLK_WORLD_15 = 175,
 SDLK_WORLD_16 = 176,
 SDLK_WORLD_17 = 177,
 SDLK_WORLD_18 = 178,
 SDLK_WORLD_19 = 179,
 SDLK_WORLD_20 = 180,
 SDLK_WORLD_21 = 181,
 SDLK_WORLD_22 = 182,
 SDLK_WORLD_23 = 183,
 SDLK_WORLD_24 = 184,
 SDLK_WORLD_25 = 185,
 SDLK_WORLD_26 = 186,
 SDLK_WORLD_27 = 187,
 SDLK_WORLD_28 = 188,
 SDLK_WORLD_29 = 189,
 SDLK_WORLD_30 = 190,
 SDLK_WORLD_31 = 191,
 SDLK_WORLD_32 = 192,
 SDLK_WORLD_33 = 193,
 SDLK_WORLD_34 = 194,
 SDLK_WORLD_35 = 195,
 SDLK_WORLD_36 = 196,
 SDLK_WORLD_37 = 197,
 SDLK_WORLD_38 = 198,
 SDLK_WORLD_39 = 199,
 SDLK_WORLD_40 = 200,
 SDLK_WORLD_41 = 201,
 SDLK_WORLD_42 = 202,
 SDLK_WORLD_43 = 203,
 SDLK_WORLD_44 = 204,
 SDLK_WORLD_45 = 205,
 SDLK_WORLD_46 = 206,
 SDLK_WORLD_47 = 207,
 SDLK_WORLD_48 = 208,
 SDLK_WORLD_49 = 209,
 SDLK_WORLD_50 = 210,
 SDLK_WORLD_51 = 211,
 SDLK_WORLD_52 = 212,
 SDLK_WORLD_53 = 213,
 SDLK_WORLD_54 = 214,
 SDLK_WORLD_55 = 215,
 SDLK_WORLD_56 = 216,
 SDLK_WORLD_57 = 217,
 SDLK_WORLD_58 = 218,
 SDLK_WORLD_59 = 219,
 SDLK_WORLD_60 = 220,
 SDLK_WORLD_61 = 221,
 SDLK_WORLD_62 = 222,
 SDLK_WORLD_63 = 223,
 SDLK_WORLD_64 = 224,
 SDLK_WORLD_65 = 225,
 SDLK_WORLD_66 = 226,
 SDLK_WORLD_67 = 227,
 SDLK_WORLD_68 = 228,
 SDLK_WORLD_69 = 229,
 SDLK_WORLD_70 = 230,
 SDLK_WORLD_71 = 231,
 SDLK_WORLD_72 = 232,
 SDLK_WORLD_73 = 233,
 SDLK_WORLD_74 = 234,
 SDLK_WORLD_75 = 235,
 SDLK_WORLD_76 = 236,
 SDLK_WORLD_77 = 237,
 SDLK_WORLD_78 = 238,
 SDLK_WORLD_79 = 239,
 SDLK_WORLD_80 = 240,
 SDLK_WORLD_81 = 241,
 SDLK_WORLD_82 = 242,
 SDLK_WORLD_83 = 243,
 SDLK_WORLD_84 = 244,
 SDLK_WORLD_85 = 245,
 SDLK_WORLD_86 = 246,
 SDLK_WORLD_87 = 247,
 SDLK_WORLD_88 = 248,
 SDLK_WORLD_89 = 249,
 SDLK_WORLD_90 = 250,
 SDLK_WORLD_91 = 251,
 SDLK_WORLD_92 = 252,
 SDLK_WORLD_93 = 253,
 SDLK_WORLD_94 = 254,
 SDLK_WORLD_95 = 255,




 SDLK_KP0 = 256,
 SDLK_KP1 = 257,
 SDLK_KP2 = 258,
 SDLK_KP3 = 259,
 SDLK_KP4 = 260,
 SDLK_KP5 = 261,
 SDLK_KP6 = 262,
 SDLK_KP7 = 263,
 SDLK_KP8 = 264,
 SDLK_KP9 = 265,
 SDLK_KP_PERIOD = 266,
 SDLK_KP_DIVIDE = 267,
 SDLK_KP_MULTIPLY = 268,
 SDLK_KP_MINUS = 269,
 SDLK_KP_PLUS = 270,
 SDLK_KP_ENTER = 271,
 SDLK_KP_EQUALS = 272,




 SDLK_UP = 273,
 SDLK_DOWN = 274,
 SDLK_RIGHT = 275,
 SDLK_LEFT = 276,
 SDLK_INSERT = 277,
 SDLK_HOME = 278,
 SDLK_END = 279,
 SDLK_PAGEUP = 280,
 SDLK_PAGEDOWN = 281,




 SDLK_F1 = 282,
 SDLK_F2 = 283,
 SDLK_F3 = 284,
 SDLK_F4 = 285,
 SDLK_F5 = 286,
 SDLK_F6 = 287,
 SDLK_F7 = 288,
 SDLK_F8 = 289,
 SDLK_F9 = 290,
 SDLK_F10 = 291,
 SDLK_F11 = 292,
 SDLK_F12 = 293,
 SDLK_F13 = 294,
 SDLK_F14 = 295,
 SDLK_F15 = 296,




 SDLK_NUMLOCK = 300,
 SDLK_CAPSLOCK = 301,
 SDLK_SCROLLOCK = 302,
 SDLK_RSHIFT = 303,
 SDLK_LSHIFT = 304,
 SDLK_RCTRL = 305,
 SDLK_LCTRL = 306,
 SDLK_RALT = 307,
 SDLK_LALT = 308,
 SDLK_RMETA = 309,
 SDLK_LMETA = 310,
 SDLK_LSUPER = 311,
 SDLK_RSUPER = 312,
 SDLK_MODE = 313,
 SDLK_COMPOSE = 314,




 SDLK_HELP = 315,
 SDLK_PRINT = 316,
 SDLK_SYSREQ = 317,
 SDLK_BREAK = 318,
 SDLK_MENU = 319,
 SDLK_POWER = 320,
 SDLK_EURO = 321,
 SDLK_UNDO = 322,




 SDLK_LAST
} SDLKey;


typedef enum {
 KMOD_NONE = 0x0000,
 KMOD_LSHIFT= 0x0001,
 KMOD_RSHIFT= 0x0002,
 KMOD_LCTRL = 0x0040,
 KMOD_RCTRL = 0x0080,
 KMOD_LALT = 0x0100,
 KMOD_RALT = 0x0200,
 KMOD_LMETA = 0x0400,
 KMOD_RMETA = 0x0800,
 KMOD_NUM = 0x1000,
 KMOD_CAPS = 0x2000,
 KMOD_MODE = 0x4000,
 KMOD_RESERVED = 0x8000
} SDLMod;
# 33 "/usr/local/include/SDL/SDL_keyboard.h" 2 3

# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_keyboard.h" 2 3
# 59 "/usr/local/include/SDL/SDL_keyboard.h" 3
typedef struct SDL_keysym {
 Uint8 scancode;
 SDLKey sym;
 SDLMod mod;
 Uint16 unicode;
} SDL_keysym;
# 82 "/usr/local/include/SDL/SDL_keyboard.h" 3
extern __attribute__ ((visibility("default"))) int SDL_EnableUNICODE(int enable);
# 98 "/usr/local/include/SDL/SDL_keyboard.h" 3
extern __attribute__ ((visibility("default"))) int SDL_EnableKeyRepeat(int delay, int interval);
extern __attribute__ ((visibility("default"))) void SDL_GetKeyRepeat(int *delay, int *interval);
# 110 "/usr/local/include/SDL/SDL_keyboard.h" 3
extern __attribute__ ((visibility("default"))) Uint8 * SDL_GetKeyState(int *numkeys);




extern __attribute__ ((visibility("default"))) SDLMod SDL_GetModState(void);





extern __attribute__ ((visibility("default"))) void SDL_SetModState(SDLMod modstate);




extern __attribute__ ((visibility("default"))) char * SDL_GetKeyName(SDLKey key);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 134 "/usr/local/include/SDL/SDL_keyboard.h" 2 3
# 35 "/usr/local/include/SDL/SDL_events.h" 2 3
# 1 "/usr/local/include/SDL/SDL_mouse.h" 1 3
# 32 "/usr/local/include/SDL/SDL_mouse.h" 3
# 1 "/usr/local/include/SDL/SDL_video.h" 1 3
# 34 "/usr/local/include/SDL/SDL_video.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_video.h" 2 3
# 50 "/usr/local/include/SDL/SDL_video.h" 3
typedef struct SDL_Rect {
 Sint16 x, y;
 Uint16 w, h;
} SDL_Rect;

typedef struct SDL_Color {
 Uint8 r;
 Uint8 g;
 Uint8 b;
 Uint8 unused;
} SDL_Color;


typedef struct SDL_Palette {
 int ncolors;
 SDL_Color *colors;
} SDL_Palette;



typedef struct SDL_PixelFormat {
 SDL_Palette *palette;
 Uint8 BitsPerPixel;
 Uint8 BytesPerPixel;
 Uint8 Rloss;
 Uint8 Gloss;
 Uint8 Bloss;
 Uint8 Aloss;
 Uint8 Rshift;
 Uint8 Gshift;
 Uint8 Bshift;
 Uint8 Ashift;
 Uint32 Rmask;
 Uint32 Gmask;
 Uint32 Bmask;
 Uint32 Amask;


 Uint32 colorkey;

 Uint8 alpha;
} SDL_PixelFormat;




typedef struct SDL_Surface {
 Uint32 flags;
 SDL_PixelFormat *format;
 int w, h;
 Uint16 pitch;
 void *pixels;
 int offset;


 struct private_hwdata *hwdata;


 SDL_Rect clip_rect;
 Uint32 unused1;


 Uint32 locked;


 struct SDL_BlitMap *map;


 unsigned int format_version;


 int refcount;
} SDL_Surface;
# 166 "/usr/local/include/SDL/SDL_video.h" 3
typedef int (*SDL_blit)(struct SDL_Surface *src, SDL_Rect *srcrect,
   struct SDL_Surface *dst, SDL_Rect *dstrect);



typedef struct SDL_VideoInfo {
 Uint32 hw_available :1;
 Uint32 wm_available :1;
 Uint32 UnusedBits1 :6;
 Uint32 UnusedBits2 :1;
 Uint32 blit_hw :1;
 Uint32 blit_hw_CC :1;
 Uint32 blit_hw_A :1;
 Uint32 blit_sw :1;
 Uint32 blit_sw_CC :1;
 Uint32 blit_sw_A :1;
 Uint32 blit_fill :1;
 Uint32 UnusedBits3 :16;
 Uint32 video_mem;
 SDL_PixelFormat *vfmt;
 int current_w;
 int current_h;
} SDL_VideoInfo;
# 208 "/usr/local/include/SDL/SDL_video.h" 3
typedef struct SDL_Overlay {
 Uint32 format;
 int w, h;
 int planes;
 Uint16 *pitches;
 Uint8 **pixels;



 struct private_yuvhwfuncs *hwfuncs;
 struct private_yuvhwdata *hwdata;




 Uint32 hw_overlay :1;
 Uint32 UnusedBits :31;

} SDL_Overlay;



typedef enum {
    SDL_GL_RED_SIZE,
    SDL_GL_GREEN_SIZE,
    SDL_GL_BLUE_SIZE,
    SDL_GL_ALPHA_SIZE,
    SDL_GL_BUFFER_SIZE,
    SDL_GL_DOUBLEBUFFER,
    SDL_GL_DEPTH_SIZE,
    SDL_GL_STENCIL_SIZE,
    SDL_GL_ACCUM_RED_SIZE,
    SDL_GL_ACCUM_GREEN_SIZE,
    SDL_GL_ACCUM_BLUE_SIZE,
    SDL_GL_ACCUM_ALPHA_SIZE,
    SDL_GL_STEREO,
    SDL_GL_MULTISAMPLEBUFFERS,
    SDL_GL_MULTISAMPLESAMPLES,
    SDL_GL_ACCELERATED_VISUAL,
    SDL_GL_SWAP_CONTROL
} SDL_GLattr;
# 275 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_VideoInit(const char *driver_name, Uint32 flags);
extern __attribute__ ((visibility("default"))) void SDL_VideoQuit(void);







extern __attribute__ ((visibility("default"))) char * SDL_VideoDriverName(char *namebuf, int maxlen);







extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_GetVideoSurface(void);







extern __attribute__ ((visibility("default"))) const SDL_VideoInfo * SDL_GetVideoInfo(void);
# 313 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_VideoModeOK(int width, int height, int bpp, Uint32 flags);
# 324 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Rect ** SDL_ListModes(SDL_PixelFormat *format, Uint32 flags);
# 384 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_SetVideoMode
   (int width, int height, int bpp, Uint32 flags);
# 394 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) void SDL_UpdateRects
  (SDL_Surface *screen, int numrects, SDL_Rect *rects);




extern __attribute__ ((visibility("default"))) void SDL_UpdateRect
  (SDL_Surface *screen, Sint32 x, Sint32 y, Uint32 w, Uint32 h);
# 414 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_Flip(SDL_Surface *screen);
# 424 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetGamma(float red, float green, float blue);
# 438 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetGammaRamp(const Uint16 *red, const Uint16 *green, const Uint16 *blue);
# 449 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_GetGammaRamp(Uint16 *red, Uint16 *green, Uint16 *blue);
# 466 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetColors(SDL_Surface *surface,
   SDL_Color *colors, int firstcolor, int ncolors);
# 485 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetPalette(SDL_Surface *surface, int flags,
       SDL_Color *colors, int firstcolor,
       int ncolors);




extern __attribute__ ((visibility("default"))) Uint32 SDL_MapRGB
(const SDL_PixelFormat * const format,
 const Uint8 r, const Uint8 g, const Uint8 b);




extern __attribute__ ((visibility("default"))) Uint32 SDL_MapRGBA
(const SDL_PixelFormat * const format,
 const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);




extern __attribute__ ((visibility("default"))) void SDL_GetRGB(Uint32 pixel,
    const SDL_PixelFormat * const fmt,
    Uint8 *r, Uint8 *g, Uint8 *b);




extern __attribute__ ((visibility("default"))) void SDL_GetRGBA(Uint32 pixel,
    const SDL_PixelFormat * const fmt,
    Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
# 553 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_CreateRGBSurface
   (Uint32 flags, int width, int height, int depth,
   Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);

extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_CreateRGBSurfaceFrom(void *pixels,
   int width, int height, int depth, int pitch,
   Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
extern __attribute__ ((visibility("default"))) void SDL_FreeSurface(SDL_Surface *surface);
# 580 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_LockSurface(SDL_Surface *surface);
extern __attribute__ ((visibility("default"))) void SDL_UnlockSurface(SDL_Surface *surface);







extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_LoadBMP_RW(SDL_RWops *src, int freesrc);
# 599 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SaveBMP_RW
  (SDL_Surface *surface, SDL_RWops *dst, int freedst);
# 615 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetColorKey
   (SDL_Surface *surface, Uint32 flag, Uint32 key);
# 633 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetAlpha(SDL_Surface *surface, Uint32 flag, Uint8 alpha);
# 647 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_bool SDL_SetClipRect(SDL_Surface *surface, const SDL_Rect *rect);






extern __attribute__ ((visibility("default"))) void SDL_GetClipRect(SDL_Surface *surface, SDL_Rect *rect);
# 668 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_ConvertSurface
   (SDL_Surface *src, SDL_PixelFormat *fmt, Uint32 flags);
# 748 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_UpperBlit
   (SDL_Surface *src, SDL_Rect *srcrect,
    SDL_Surface *dst, SDL_Rect *dstrect);



extern __attribute__ ((visibility("default"))) int SDL_LowerBlit
   (SDL_Surface *src, SDL_Rect *srcrect,
    SDL_Surface *dst, SDL_Rect *dstrect);
# 767 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_FillRect
  (SDL_Surface *dst, SDL_Rect *dstrect, Uint32 color);
# 781 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_DisplayFormat(SDL_Surface *surface);
# 795 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Surface * SDL_DisplayFormatAlpha(SDL_Surface *surface);
# 807 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_Overlay * SDL_CreateYUVOverlay(int width, int height,
    Uint32 format, SDL_Surface *display);


extern __attribute__ ((visibility("default"))) int SDL_LockYUVOverlay(SDL_Overlay *overlay);
extern __attribute__ ((visibility("default"))) void SDL_UnlockYUVOverlay(SDL_Overlay *overlay);







extern __attribute__ ((visibility("default"))) int SDL_DisplayYUVOverlay(SDL_Overlay *overlay, SDL_Rect *dstrect);


extern __attribute__ ((visibility("default"))) void SDL_FreeYUVOverlay(SDL_Overlay *overlay);
# 837 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_GL_LoadLibrary(const char *path);




extern __attribute__ ((visibility("default"))) void * SDL_GL_GetProcAddress(const char* proc);




extern __attribute__ ((visibility("default"))) int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
# 858 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_GL_GetAttribute(SDL_GLattr attr, int* value);




extern __attribute__ ((visibility("default"))) void SDL_GL_SwapBuffers(void);






extern __attribute__ ((visibility("default"))) void SDL_GL_UpdateRects(int numrects, SDL_Rect* rects);
extern __attribute__ ((visibility("default"))) void SDL_GL_Lock(void);
extern __attribute__ ((visibility("default"))) void SDL_GL_Unlock(void);
# 885 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) void SDL_WM_SetCaption(const char *title, const char *icon);



extern __attribute__ ((visibility("default"))) void SDL_WM_GetCaption(char **title, char **icon);







extern __attribute__ ((visibility("default"))) void SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask);






extern __attribute__ ((visibility("default"))) int SDL_WM_IconifyWindow(void);
# 921 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) int SDL_WM_ToggleFullScreen(SDL_Surface *surface);

typedef enum {
 SDL_GRAB_QUERY = -1,
 SDL_GRAB_OFF = 0,
 SDL_GRAB_ON = 1,
 SDL_GRAB_FULLSCREEN
} SDL_GrabMode;
# 937 "/usr/local/include/SDL/SDL_video.h" 3
extern __attribute__ ((visibility("default"))) SDL_GrabMode SDL_WM_GrabInput(SDL_GrabMode mode);




extern __attribute__ ((visibility("default"))) int SDL_SoftStretch(SDL_Surface *src, SDL_Rect *srcrect,
                                    SDL_Surface *dst, SDL_Rect *dstrect);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 950 "/usr/local/include/SDL/SDL_video.h" 2 3
# 33 "/usr/local/include/SDL/SDL_mouse.h" 2 3

# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 35 "/usr/local/include/SDL/SDL_mouse.h" 2 3





typedef struct WMcursor WMcursor;
typedef struct SDL_Cursor {
 SDL_Rect area;
 Sint16 hot_x, hot_y;
 Uint8 *data;
 Uint8 *mask;
 Uint8 *save[2];
 WMcursor *wm_cursor;
} SDL_Cursor;
# 57 "/usr/local/include/SDL/SDL_mouse.h" 3
extern __attribute__ ((visibility("default"))) Uint8 SDL_GetMouseState(int *x, int *y);







extern __attribute__ ((visibility("default"))) Uint8 SDL_GetRelativeMouseState(int *x, int *y);




extern __attribute__ ((visibility("default"))) void SDL_WarpMouse(Uint16 x, Uint16 y);
# 85 "/usr/local/include/SDL/SDL_mouse.h" 3
extern __attribute__ ((visibility("default"))) SDL_Cursor * SDL_CreateCursor
  (Uint8 *data, Uint8 *mask, int w, int h, int hot_x, int hot_y);






extern __attribute__ ((visibility("default"))) void SDL_SetCursor(SDL_Cursor *cursor);




extern __attribute__ ((visibility("default"))) SDL_Cursor * SDL_GetCursor(void);




extern __attribute__ ((visibility("default"))) void SDL_FreeCursor(SDL_Cursor *cursor);
# 112 "/usr/local/include/SDL/SDL_mouse.h" 3
extern __attribute__ ((visibility("default"))) int SDL_ShowCursor(int toggle);
# 141 "/usr/local/include/SDL/SDL_mouse.h" 3
# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 142 "/usr/local/include/SDL/SDL_mouse.h" 2 3
# 36 "/usr/local/include/SDL/SDL_events.h" 2 3
# 1 "/usr/local/include/SDL/SDL_joystick.h" 1 3
# 33 "/usr/local/include/SDL/SDL_joystick.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 34 "/usr/local/include/SDL/SDL_joystick.h" 2 3
# 46 "/usr/local/include/SDL/SDL_joystick.h" 3
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;





extern __attribute__ ((visibility("default"))) int SDL_NumJoysticks(void);







extern __attribute__ ((visibility("default"))) const char * SDL_JoystickName(int device_index);
# 73 "/usr/local/include/SDL/SDL_joystick.h" 3
extern __attribute__ ((visibility("default"))) SDL_Joystick * SDL_JoystickOpen(int device_index);




extern __attribute__ ((visibility("default"))) int SDL_JoystickOpened(int device_index);




extern __attribute__ ((visibility("default"))) int SDL_JoystickIndex(SDL_Joystick *joystick);




extern __attribute__ ((visibility("default"))) int SDL_JoystickNumAxes(SDL_Joystick *joystick);







extern __attribute__ ((visibility("default"))) int SDL_JoystickNumBalls(SDL_Joystick *joystick);




extern __attribute__ ((visibility("default"))) int SDL_JoystickNumHats(SDL_Joystick *joystick);




extern __attribute__ ((visibility("default"))) int SDL_JoystickNumButtons(SDL_Joystick *joystick);







extern __attribute__ ((visibility("default"))) void SDL_JoystickUpdate(void);
# 125 "/usr/local/include/SDL/SDL_joystick.h" 3
extern __attribute__ ((visibility("default"))) int SDL_JoystickEventState(int state);
# 134 "/usr/local/include/SDL/SDL_joystick.h" 3
extern __attribute__ ((visibility("default"))) Sint16 SDL_JoystickGetAxis(SDL_Joystick *joystick, int axis);
# 157 "/usr/local/include/SDL/SDL_joystick.h" 3
extern __attribute__ ((visibility("default"))) Uint8 SDL_JoystickGetHat(SDL_Joystick *joystick, int hat);
# 166 "/usr/local/include/SDL/SDL_joystick.h" 3
extern __attribute__ ((visibility("default"))) int SDL_JoystickGetBall(SDL_Joystick *joystick, int ball, int *dx, int *dy);






extern __attribute__ ((visibility("default"))) Uint8 SDL_JoystickGetButton(SDL_Joystick *joystick, int button);




extern __attribute__ ((visibility("default"))) void SDL_JoystickClose(SDL_Joystick *joystick);






# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 186 "/usr/local/include/SDL/SDL_joystick.h" 2 3
# 37 "/usr/local/include/SDL/SDL_events.h" 2 3
# 1 "/usr/local/include/SDL/SDL_quit.h" 1 3
# 38 "/usr/local/include/SDL/SDL_events.h" 2 3

# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 40 "/usr/local/include/SDL/SDL_events.h" 2 3
# 52 "/usr/local/include/SDL/SDL_events.h" 3
typedef enum {
       SDL_NOEVENT = 0,
       SDL_ACTIVEEVENT,
       SDL_KEYDOWN,
       SDL_KEYUP,
       SDL_MOUSEMOTION,
       SDL_MOUSEBUTTONDOWN,
       SDL_MOUSEBUTTONUP,
       SDL_JOYAXISMOTION,
       SDL_JOYBALLMOTION,
       SDL_JOYHATMOTION,
       SDL_JOYBUTTONDOWN,
       SDL_JOYBUTTONUP,
       SDL_QUIT,
       SDL_SYSWMEVENT,
       SDL_EVENT_RESERVEDA,
       SDL_EVENT_RESERVEDB,
       SDL_VIDEORESIZE,
       SDL_VIDEOEXPOSE,
       SDL_EVENT_RESERVED2,
       SDL_EVENT_RESERVED3,
       SDL_EVENT_RESERVED4,
       SDL_EVENT_RESERVED5,
       SDL_EVENT_RESERVED6,
       SDL_EVENT_RESERVED7,

       SDL_USEREVENT = 24,



       SDL_NUMEVENTS = 32
} SDL_EventType;




typedef enum {
 SDL_ACTIVEEVENTMASK = (1<<(SDL_ACTIVEEVENT)),
 SDL_KEYDOWNMASK = (1<<(SDL_KEYDOWN)),
 SDL_KEYUPMASK = (1<<(SDL_KEYUP)),
 SDL_KEYEVENTMASK = (1<<(SDL_KEYDOWN))|
                           (1<<(SDL_KEYUP)),
 SDL_MOUSEMOTIONMASK = (1<<(SDL_MOUSEMOTION)),
 SDL_MOUSEBUTTONDOWNMASK = (1<<(SDL_MOUSEBUTTONDOWN)),
 SDL_MOUSEBUTTONUPMASK = (1<<(SDL_MOUSEBUTTONUP)),
 SDL_MOUSEEVENTMASK = (1<<(SDL_MOUSEMOTION))|
                           (1<<(SDL_MOUSEBUTTONDOWN))|
                           (1<<(SDL_MOUSEBUTTONUP)),
 SDL_JOYAXISMOTIONMASK = (1<<(SDL_JOYAXISMOTION)),
 SDL_JOYBALLMOTIONMASK = (1<<(SDL_JOYBALLMOTION)),
 SDL_JOYHATMOTIONMASK = (1<<(SDL_JOYHATMOTION)),
 SDL_JOYBUTTONDOWNMASK = (1<<(SDL_JOYBUTTONDOWN)),
 SDL_JOYBUTTONUPMASK = (1<<(SDL_JOYBUTTONUP)),
 SDL_JOYEVENTMASK = (1<<(SDL_JOYAXISMOTION))|
                           (1<<(SDL_JOYBALLMOTION))|
                           (1<<(SDL_JOYHATMOTION))|
                           (1<<(SDL_JOYBUTTONDOWN))|
                           (1<<(SDL_JOYBUTTONUP)),
 SDL_VIDEORESIZEMASK = (1<<(SDL_VIDEORESIZE)),
 SDL_VIDEOEXPOSEMASK = (1<<(SDL_VIDEOEXPOSE)),
 SDL_QUITMASK = (1<<(SDL_QUIT)),
 SDL_SYSWMEVENTMASK = (1<<(SDL_SYSWMEVENT))
} SDL_EventMask ;




typedef struct SDL_ActiveEvent {
 Uint8 type;
 Uint8 gain;
 Uint8 state;
} SDL_ActiveEvent;


typedef struct SDL_KeyboardEvent {
 Uint8 type;
 Uint8 which;
 Uint8 state;
 SDL_keysym keysym;
} SDL_KeyboardEvent;


typedef struct SDL_MouseMotionEvent {
 Uint8 type;
 Uint8 which;
 Uint8 state;
 Uint16 x, y;
 Sint16 xrel;
 Sint16 yrel;
} SDL_MouseMotionEvent;


typedef struct SDL_MouseButtonEvent {
 Uint8 type;
 Uint8 which;
 Uint8 button;
 Uint8 state;
 Uint16 x, y;
} SDL_MouseButtonEvent;


typedef struct SDL_JoyAxisEvent {
 Uint8 type;
 Uint8 which;
 Uint8 axis;
 Sint16 value;
} SDL_JoyAxisEvent;


typedef struct SDL_JoyBallEvent {
 Uint8 type;
 Uint8 which;
 Uint8 ball;
 Sint16 xrel;
 Sint16 yrel;
} SDL_JoyBallEvent;


typedef struct SDL_JoyHatEvent {
 Uint8 type;
 Uint8 which;
 Uint8 hat;
 Uint8 value;





} SDL_JoyHatEvent;


typedef struct SDL_JoyButtonEvent {
 Uint8 type;
 Uint8 which;
 Uint8 button;
 Uint8 state;
} SDL_JoyButtonEvent;





typedef struct SDL_ResizeEvent {
 Uint8 type;
 int w;
 int h;
} SDL_ResizeEvent;


typedef struct SDL_ExposeEvent {
 Uint8 type;
} SDL_ExposeEvent;


typedef struct SDL_QuitEvent {
 Uint8 type;
} SDL_QuitEvent;


typedef struct SDL_UserEvent {
 Uint8 type;
 int code;
 void *data1;
 void *data2;
} SDL_UserEvent;


struct SDL_SysWMmsg;
typedef struct SDL_SysWMmsg SDL_SysWMmsg;
typedef struct SDL_SysWMEvent {
 Uint8 type;
 SDL_SysWMmsg *msg;
} SDL_SysWMEvent;


typedef union SDL_Event {
 Uint8 type;
 SDL_ActiveEvent active;
 SDL_KeyboardEvent key;
 SDL_MouseMotionEvent motion;
 SDL_MouseButtonEvent button;
 SDL_JoyAxisEvent jaxis;
 SDL_JoyBallEvent jball;
 SDL_JoyHatEvent jhat;
 SDL_JoyButtonEvent jbutton;
 SDL_ResizeEvent resize;
 SDL_ExposeEvent expose;
 SDL_QuitEvent quit;
 SDL_UserEvent user;
 SDL_SysWMEvent syswm;
} SDL_Event;
# 251 "/usr/local/include/SDL/SDL_events.h" 3
extern __attribute__ ((visibility("default"))) void SDL_PumpEvents(void);

typedef enum {
 SDL_ADDEVENT,
 SDL_PEEKEVENT,
 SDL_GETEVENT
} SDL_eventaction;
# 277 "/usr/local/include/SDL/SDL_events.h" 3
extern __attribute__ ((visibility("default"))) int SDL_PeepEvents(SDL_Event *events, int numevents,
    SDL_eventaction action, Uint32 mask);





extern __attribute__ ((visibility("default"))) int SDL_PollEvent(SDL_Event *event);





extern __attribute__ ((visibility("default"))) int SDL_WaitEvent(SDL_Event *event);





extern __attribute__ ((visibility("default"))) int SDL_PushEvent(SDL_Event *event);



typedef int ( *SDL_EventFilter)(const SDL_Event *event);
# 323 "/usr/local/include/SDL/SDL_events.h" 3
extern __attribute__ ((visibility("default"))) void SDL_SetEventFilter(SDL_EventFilter filter);





extern __attribute__ ((visibility("default"))) SDL_EventFilter SDL_GetEventFilter(void);
# 348 "/usr/local/include/SDL/SDL_events.h" 3
extern __attribute__ ((visibility("default"))) Uint8 SDL_EventState(Uint8 type, int state);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 355 "/usr/local/include/SDL/SDL_events.h" 2 3
# 38 "/usr/local/include/SDL/SDL.h" 2 3
# 1 "/usr/local/include/SDL/SDL_loadso.h" 1 3
# 49 "/usr/local/include/SDL/SDL_loadso.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 50 "/usr/local/include/SDL/SDL_loadso.h" 2 3
# 60 "/usr/local/include/SDL/SDL_loadso.h" 3
extern __attribute__ ((visibility("default"))) void * SDL_LoadObject(const char *sofile);






extern __attribute__ ((visibility("default"))) void * SDL_LoadFunction(void *handle, const char *name);


extern __attribute__ ((visibility("default"))) void SDL_UnloadObject(void *handle);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 77 "/usr/local/include/SDL/SDL_loadso.h" 2 3
# 39 "/usr/local/include/SDL/SDL.h" 2 3



# 1 "/usr/local/include/SDL/SDL_timer.h" 1 3
# 33 "/usr/local/include/SDL/SDL_timer.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 34 "/usr/local/include/SDL/SDL_timer.h" 2 3
# 49 "/usr/local/include/SDL/SDL_timer.h" 3
extern __attribute__ ((visibility("default"))) Uint32 SDL_GetTicks(void);


extern __attribute__ ((visibility("default"))) void SDL_Delay(Uint32 ms);


typedef Uint32 ( *SDL_TimerCallback)(Uint32 interval);
# 86 "/usr/local/include/SDL/SDL_timer.h" 3
extern __attribute__ ((visibility("default"))) int SDL_SetTimer(Uint32 interval, SDL_TimerCallback callback);
# 101 "/usr/local/include/SDL/SDL_timer.h" 3
typedef Uint32 ( *SDL_NewTimerCallback)(Uint32 interval, void *param);


typedef struct _SDL_TimerID *SDL_TimerID;




extern __attribute__ ((visibility("default"))) SDL_TimerID SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void *param);





extern __attribute__ ((visibility("default"))) SDL_bool SDL_RemoveTimer(SDL_TimerID t);







# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 124 "/usr/local/include/SDL/SDL_timer.h" 2 3
# 43 "/usr/local/include/SDL/SDL.h" 2 3

# 1 "/usr/local/include/SDL/SDL_version.h" 1 3
# 32 "/usr/local/include/SDL/SDL_version.h" 3
# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 33 "/usr/local/include/SDL/SDL_version.h" 2 3
# 47 "/usr/local/include/SDL/SDL_version.h" 3
typedef struct SDL_version {
 Uint8 major;
 Uint8 minor;
 Uint8 patch;
} SDL_version;
# 83 "/usr/local/include/SDL/SDL_version.h" 3
extern __attribute__ ((visibility("default"))) const SDL_version * SDL_Linked_Version(void);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 90 "/usr/local/include/SDL/SDL_version.h" 2 3
# 45 "/usr/local/include/SDL/SDL.h" 2 3

# 1 "/usr/local/include/SDL/begin_code.h" 1 3
# 47 "/usr/local/include/SDL/SDL.h" 2 3
# 76 "/usr/local/include/SDL/SDL.h" 3
extern __attribute__ ((visibility("default"))) int SDL_Init(Uint32 flags);


extern __attribute__ ((visibility("default"))) int SDL_InitSubSystem(Uint32 flags);


extern __attribute__ ((visibility("default"))) void SDL_QuitSubSystem(Uint32 flags);





extern __attribute__ ((visibility("default"))) Uint32 SDL_WasInit(Uint32 flags);




extern __attribute__ ((visibility("default"))) void SDL_Quit(void);





# 1 "/usr/local/include/SDL/close_code.h" 1 3
# 100 "/usr/local/include/SDL/SDL.h" 2 3
# 45 "source/SDL_rotozoom.h" 2
# 79 "source/SDL_rotozoom.h"
 extern SDL_Surface *rotozoomSurface(SDL_Surface * src, double angle, double zoom, int smooth);

 extern SDL_Surface *rotozoomSurfaceXY
  (SDL_Surface * src, double angle, double zoomx, double zoomy, int smooth);


 extern void rotozoomSurfaceSize(int width, int height, double angle, double zoom, int *dstwidth,
  int *dstheight);

 extern void rotozoomSurfaceSizeXY
  (int width, int height, double angle, double zoomx, double zoomy,
  int *dstwidth, int *dstheight);







 extern SDL_Surface *zoomSurface(SDL_Surface * src, double zoomx, double zoomy, int smooth);

 extern void zoomSurfaceSize(int width, int height, double zoomx, double zoomy, int *dstwidth, int *dstheight);







 extern SDL_Surface *shrinkSurface(SDL_Surface * src, int factorx, int factory);







 extern SDL_Surface* rotateSurface90Degrees(SDL_Surface* src, int numClockwiseTurns);
# 17 "source/video.c" 2


# 1 "/usr/local/include/SDL/SDL_thread.h" 1 3
# 20 "source/video.c" 2
# 78 "source/video.c"
int shouldFillBuffers = 0;
int shouldRedraw = 0;
int drawingComplete = 0;
int buffersFull = 0;
int spriteTableChanged = 1;

int BGDrawBuffer[160][144];
int windowDrawBuffer[160][144];
int spriteBackBuffer[160][144];
int spriteFrontBuffer[160][144];

SDL_Surface *display;

SDL_sem *drawVideoStartSem;
SDL_sem *drawVideoCompleteSem;
SDL_sem *fillBuffersSem;
SDL_sem *spriteStartSem;
SDL_sem *windowStartSem;
SDL_sem *backgroundStartSem;
SDL_sem *spriteEndSem;
SDL_sem *windowEndSem;
SDL_sem *backgroundEndSem;

typedef int drawBuffer[160][144];

typedef struct tileLine_T {
 char lowBits;
 char highBits;
}__attribute__((packed)) tileLine;

typedef struct tileData_t {
 tileLine lines[8];
}__attribute__((packed)) tileData;

typedef struct SpriteList_t {
 int spriteNum;
 struct SpriteList_t* next;
} SpriteList;

typedef struct OAMEntry_t {
 unsigned char Y;
 unsigned char X;
 unsigned char tile;
 unsigned char flags;
}__attribute__((packed)) OAMEntry;

SpriteList* firstSprite;

void dummyFunct2(){
 return;
}

void spriteListInsert(SpriteList** first,SpriteList* insertPoint,int spriteNum){

 if(insertPoint == ((void *)0)){
  return;
 }

 SpriteList *newElement = (SpriteList*)malloc_line(sizeof(newElement),136,"source/video.c");
 if(newElement == ((void *)0)){
  printf("Couldn't Allocate room for new Sprite!!!\n");
  exit(1);
 }
 SpriteList *searchElement = *first;

 newElement->spriteNum = spriteNum;
 if(insertPoint==*first){
  newElement->next = *first;
  *first = newElement;
 } else {
  while(searchElement->next != insertPoint){
   searchElement = searchElement->next;
   if(searchElement == ((void *)0)){
    return;
   }
  }
  newElement->next = insertPoint;
  searchElement->next = newElement;
 }
}

void spriteListDelete(SpriteList** first,SpriteList* deletePoint){
 if(*first == deletePoint){
  SpriteList* tempSprite;
  tempSprite = *first;
  *first = tempSprite->next;
  free(tempSprite);
  return;
 }

 SpriteList* searchElement = *first;

 while(searchElement->next != deletePoint){
  searchElement = searchElement->next;
  if(searchElement==((void *)0)){
   return;
  }
 }
 searchElement->next = deletePoint->next;
 free(deletePoint);
}

SpriteList* getSpriteElement(SpriteList** first,int data){
 SpriteList *search = *first;
 while((search!=((void *)0))&&(search->spriteNum!=data)){
  search = search->next;
 }
 return search;
}

void spriteListSort(SpriteList** first,SpriteList* last){
 if(*first == ((void *)0)){
  return;
 }

 if(((*first)->next == last)||((*first) == last)){
  return;
 }

 OAMEntry* OAMTableEntries = (OAMEntry*)OAMTable;

 SpriteList *pivot = *first;
 SpriteList *currSprite = pivot->next;
 SpriteList *tempSprite;
 int pivotNum = OAMTableEntries[pivot->spriteNum].X;

 while(currSprite!=last){
  if(OAMTableEntries[currSprite->spriteNum].X<pivotNum){
   spriteListInsert(first,pivot,OAMTableEntries[currSprite->spriteNum].X);
   tempSprite = currSprite;
   currSprite = currSprite->next;
   spriteListDelete(first,tempSprite);
  } else {
   currSprite = currSprite->next;
  }
 }

 spriteListSort(first,pivot);
 spriteListSort(&pivot->next,last);
}

unsigned char getColorForTile(tileData* tile,int row, int column){
 tileLine readLine = tile->lines[row];
 char upperBit = readLine.highBits >> (7-column);
 upperBit = upperBit&1;
 char lowerBit = readLine.lowBits >> (7-column);
 lowerBit = lowerBit&1;

 return ((upperBit<<1)|lowerBit)&0x3;
}

void updateVideo(int screenRefreshCount){

 int temp;

 fillBuffersSem = SDL_CreateSemaphore(0);
 drawVideoStartSem = SDL_CreateSemaphore(0);
 drawVideoCompleteSem = SDL_CreateSemaphore(1);

 if(screenRefreshCount<65664){

  if(screenRefreshCount == 0){


   drawingComplete = 0;
   setLY(0);
   setLCDStatus((getLCDStatus()&0xFC)|2);
   shouldFillBuffers=1;



   if((getLCDStatus()&(1<<5))!=0){
    setInterrupt(2);
   }
   if(getLY()==getLYC()){
    setLCDStatus(getLCDStatus()|(1<<2));
    if(getLCDStatus()&(1<<6)){
     setInterrupt(2);
    }
   } else {
    setLCDStatus(getLCDStatus(~(1<<2)));
   }
  } else {
   temp = screenRefreshCount%456;
   if(temp==0){
    setLCDStatus((getLCDStatus()&0xFC)|2);
    setLY(getLY()+1);


    if((getLCDStatus()&(1<<5))!=0){
     setInterrupt(2);
    }

    if(getLY()==getLYC()){
     setLCDStatus(getLCDStatus()|(1<<2));
     if(getLCDStatus()&(1<<6)){
      setInterrupt(2);
     }
    } else {
     setLCDStatus(getLCDStatus()& ~(1<<2));
    }
   } else if(temp==77){
    setLCDStatus((getLCDStatus()&0xFC)|3);
   } else if(temp==249){
    setLCDStatus((getLCDStatus()&0xFC)|0);
    if((getLCDStatus()&(1<<3))){
     setInterrupt(2);
    }
   }
  }
 } else if(screenRefreshCount==65664){


  buffersFull = 0;
  shouldRedraw = 1;

  setLCDStatus((getLCDStatus()&0xFC)|1);
  setLY(getLY() + 1);

  if(getLCDStatus()&(1<<4)){
   setInterrupt(1);
  }

  if(getLY()==getLYC()){
   setLCDStatus(getLCDStatus()|(1<<2));
   if(getLCDStatus()&(1<<2)){
    setInterrupt(2);
   }
  } else {
   setLCDStatus(getLCDStatus()& ~(1<<2));
  }
 } else if((screenRefreshCount%456)==0){
  setLY(getLY()+1);
  if(getLY()==getLYC()){
   setLCDStatus(getLCDStatus()|(1<<2));
   if(getLCDStatus()&(1<<2)){
    setInterrupt(2);
   }
  } else {
   setLCDStatus(getLCDStatus()& ~(1<<2));
  }
 }
}

void putPixelSDL(int x,int y,int value,SDL_Surface *dest){
 int* displayPixels = (int*)dest->pixels;

 displayPixels[y*(160)+x] = value;
}

char getAlpha(int pixel){
# 337 "source/video.c"
 return pixel>>24;
}

int checkForWhite(int pixel){
# 351 "source/video.c"
 if((pixel&0xFFFFFF) == 0xFFFFFF){
  return 1;
 } else {
  return 0;
 }

}

void drawBGTileToBuffer(unsigned int tileNum,drawBuffer outputBuffer,int x,int y,int palette[4]){

 tileData* currTile = (tileData*)&vramBanks[tileNum*sizeof(tileData)];

 int tileRow,tileColumn;





 if((x<=-8)||(x>160)){
  return;
 }
 if((y<=-8)||(y>144)){
  return;
 }

 dummyFunct2();

 for(tileRow=0;tileRow<8;tileRow++){
  for(tileColumn=0;tileColumn<8;tileColumn++){
   if((x+tileColumn>=0)&&(x+tileColumn<160)){
    if((y+tileRow>=0)&&(y+tileRow<144)){
     outputBuffer[x+tileColumn][y+tileRow] = palette[getColorForTile(currTile,tileRow,tileColumn)];
    }
   }
  }
 }
}

void reverseTile(drawBuffer outputBuffer,int x,int y){

 int tempColor;
 int i;

 if(x<0){
  return;
 } else if(y<0){
  return;
 }

 for(i=0;i<8;i++){
  tempColor = outputBuffer[x+7][y+i];
  outputBuffer[x+7][y+i] = outputBuffer[x][y+i];
  outputBuffer[x][y+i] = tempColor;

  tempColor = outputBuffer[x+6][y+i];
  outputBuffer[x+6][y+i] = outputBuffer[x+1][y+1];
  outputBuffer[x+1][y+i] = tempColor;

  tempColor = outputBuffer[x+5][y+i];
  outputBuffer[x+5][y+i] = outputBuffer[x+2][y+i];
  outputBuffer[x+2][y+i] = tempColor;

  tempColor = outputBuffer[x+4][y+i];
  outputBuffer[x+4][y+i] = outputBuffer[x+3][y+i];
  outputBuffer[x+3][y+i] = tempColor;
 }

}



int backgroundBufferFill(void *arguments){
 void** args = (void*)arguments;

 char* backgroundBufferComplete = (char*)args[0];
 char* beginFillingBackgroundBuffer = (char*)args[1];

 int i,j;
 unsigned int currTile;
 int tileOffsetX;
 int tileOffsetY;

 unsigned char *BGTileMap = ((void *)0);

 int (*backgroundBuffer)[144] = args[2];



 int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
 int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
 int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
 int colorBlack = SDL_MapRGB(display->format,0,0,0);

 printf("white: %d\n",checkForWhite(colorWhite));

 int basePalette[4];
 basePalette[3] = colorBlack;
 basePalette[2] = colorDarkGray;
 basePalette[1] = colorLightGray;
 basePalette[0] = colorWhite;

 int bgPalette[4];



 while(1){
  while(*beginFillingBackgroundBuffer == 0);


  *beginFillingBackgroundBuffer = 0;
  *backgroundBufferComplete = 0;


  memset(backgroundBuffer,0,160*144);

  if(getLCDControl()&(1<<0)){

   if((getLCDControl()&(1<<3))==0){
    BGTileMap = vramBanks+0x1800;
   } else {
    BGTileMap = vramBanks+0x1C00;
   }

   bgPalette[0] = basePalette[getBGPaletteData()&0x3];
   bgPalette[1] = basePalette[(getBGPaletteData()&0xC)>>2];
   bgPalette[2] = basePalette[(getBGPaletteData()&0x30)>>4];
   bgPalette[3] = basePalette[(getBGPaletteData()&0xC0)>>6];

   for(i=-1;i<18;i++){
    for(j=-1;j<20;j++){

     tileOffsetX = getscrollX()/8 + j;
     if(tileOffsetX >= 32){
      tileOffsetX-=32;
     }
     tileOffsetY = getscrollY()/8 + i;
     if(tileOffsetY >= 32){
      tileOffsetY-=32;
     }

     currTile = (unsigned int)BGTileMap[tileOffsetY*32+tileOffsetX]&0xFF;

     if(getLCDControl()&(1<<4)){
      drawBGTileToBuffer(currTile&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
     } else {
      if(currTile<0x80){
       drawBGTileToBuffer((currTile+0x100)&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
      } else {
       drawBGTileToBuffer((currTile)&0x1FF,backgroundBuffer,j*8+(getscrollX()%8),i*8+(getscrollY()%8),bgPalette);
      }
     }






    }
   }

  } else {
   for(i=0;i<144;i++){
    for(j=0;j<160;j++){
     backgroundBuffer[j][i] = colorWhite;
    }
   }
  }

  *backgroundBufferComplete = 1;
  SDL_SemPost(backgroundEndSem);
 }

 return 0;
}

int windowBufferFill(void *arguments){
 void** args = (void*)arguments;

 char* windowBufferComplete = (char*)args[0];
 char* beginFillingWindowBuffer = (char*)args[1];
 int (*windowBuffer)[144] = args[2];

 int colorTransparent = SDL_MapRGBA(display->format,255,255,255,0);
 int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
 int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
 int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
 int colorBlack = SDL_MapRGB(display->format,0,0,0);

 int basePalette[4];
 basePalette[3] = colorBlack;
 basePalette[2] = colorDarkGray;
 basePalette[1] = colorLightGray;
 basePalette[0] = colorWhite;

 int windowPalette[4];


 char *BGTileMap = ((void *)0);

 int i,j;
 unsigned int currTile;

 while(1){
  while(*beginFillingWindowBuffer == 0);


  *beginFillingWindowBuffer = 0;
  *windowBufferComplete = 0;

  for(i=0;i<144;i++){
   for(j=0;j<160;j++){
    windowBuffer[j][i] = colorTransparent;
   }
  }

  if((getLCDControl()&(1<<5))!=0){


   if((getWX()<167)&&(getWY()<144)){

    if((getLCDControl()&(1<<6))==0){
     BGTileMap = (char*)(vramBanks+0x1800);
    } else {
     BGTileMap = (char*)(vramBanks+0x1C00);
    }

    windowPalette[0] = basePalette[getBGPaletteData()&0x3];
    windowPalette[1] = basePalette[(getBGPaletteData()&0xC)>>2];
    windowPalette[2] = basePalette[(getBGPaletteData()&0x30)>>4];
    windowPalette[3] = basePalette[(getBGPaletteData()&0xC0)>>6];

    for(i=0;i*8+(getWX()-7)<160;i++){
     for(j=0;j*8+getWY()<144;j++){
      currTile = BGTileMap[i*32+j];
      currTile += 128;

      drawBGTileToBuffer(0x81,windowBuffer,i*8+getWX()-7,j*8+getWY(),windowPalette);
     }
    }
   }

  }

  *windowBufferComplete = 1;

 }

 return 0;
}

int spriteBufferFill(void *arguments){
 void** args = (void*)arguments;

 char* backSpriteBufferComplete = (char*)args[0];
 char* frontSpriteBufferComplete = (char*)args[1];
 char* beginFillingSpriteBuffer = (char*)args[2];
 int (*backSpriteBuffer)[144] = args[3];
 int (*frontSpriteBuffer)[144] = args[4];

 int colorTransparent = 0xAA000000;
 int colorWhite = SDL_MapRGB(display->format,0xFF,0xFF,0xFF);
 int colorLightGray = SDL_MapRGB(display->format,0xAA,0xAA,0xAA);
 int colorDarkGray = SDL_MapRGB(display->format,0x55,0x55,0x55);
 int colorBlack = SDL_MapRGB(display->format,0,0,0);

 printf("Alpha Value of transparent: %X\n",colorTransparent);

 int basePalette[4];
 basePalette[3] = colorBlack;
 basePalette[2] = colorDarkGray;
 basePalette[1] = colorLightGray;
 basePalette[0] = colorWhite;

 int sprite0Palette[4];
 int sprite1Palette[4];

 OAMEntry *OAMTableEntry = (OAMEntry*)OAMTable;

 int numSpritesPerLine[144];
 int i,j;
 int tooManySprites;
 unsigned char spriteY,spriteX;
 char spriteTileNum,spriteFlags;

 SpriteList* firstSprite = ((void *)0);
 SpriteList* currSprite = ((void *)0);


 firstSprite = (SpriteList*)malloc_line(sizeof(SpriteList),639,"source/video.c");
 currSprite = firstSprite;
 for(i=0;i<39;i++){
  currSprite->spriteNum = i;
  currSprite->next = (SpriteList*)malloc_line(sizeof(SpriteList),643,"source/video.c");
  currSprite = currSprite->next;
 }
 currSprite->spriteNum = 39;
 currSprite->next = ((void *)0);





 while(1){
  while(*beginFillingSpriteBuffer == 0);


  *backSpriteBufferComplete = 0;
  *frontSpriteBufferComplete = 0;
  *beginFillingSpriteBuffer = 0;

  if(getLCDControl()&(1<<1)){
   if(spriteTableChanged == 1){

    spriteTableChanged = 0;
   }

   for(i=0;i<144;i++){
    numSpritesPerLine[i] = 0;
   }


   sprite0Palette[0] = colorTransparent;
   for(i=1;i<4;i++){
    switch((getobj0Palette()>>(i*2))&0x3){
     case 0:
      sprite0Palette[i] = basePalette[0];
      break;
     case 1:
      sprite0Palette[i] = basePalette[1];
      break;
     case 2:
      sprite0Palette[i] = basePalette[2];
      break;
     case 3:
      sprite0Palette[i] = basePalette[3];
      break;
    }
   }

   sprite1Palette[0] = colorTransparent;
   for(i=1;i<4;i++){
    switch((getobj1Palette()>>(i*2))&0x3){
     case 0:
      sprite1Palette[i] = basePalette[0];
      break;
     case 1:
      sprite1Palette[i] = basePalette[1];
      break;
     case 2:
      sprite1Palette[i] = basePalette[2];
      break;
     case 3:
      sprite1Palette[i] = basePalette[3];
      break;
    }
   }

   for(i=0;i<144;i++){
    for(j=0;j<160;j++){
     backSpriteBuffer[j][i] = colorTransparent;
     frontSpriteBuffer[j][i] = colorTransparent;
    }
   }





   for(currSprite = firstSprite;currSprite!=((void *)0);currSprite = currSprite->next){
    spriteY = OAMTableEntry[currSprite->spriteNum].Y;
    spriteX = OAMTableEntry[currSprite->spriteNum].X;
    spriteTileNum = OAMTableEntry[currSprite->spriteNum].tile;
    spriteFlags = OAMTableEntry[currSprite->spriteNum].flags;

    if(spriteY<160){
     tooManySprites = 0;

     for(i=0;i<8;i++){
      if((i+spriteY)>=144){
       break;
      }
      if(numSpritesPerLine[i+spriteY]>=10){
       tooManySprites = 1;
       break;
      }
     }



     if(tooManySprites == 0){


      for(i=0;i<8;i++){
       if((i+spriteY)>=144){
        break;
       }
       numSpritesPerLine[i+spriteY]++;
      }




      if((getLCDControl()&(1<<2)) == 0){

       if((spriteFlags&(1<<7))==0){

        if((spriteFlags&(1<<4))==0){
         drawBGTileToBuffer(spriteTileNum&0xFF,frontSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
        } else {
         drawBGTileToBuffer(spriteTileNum&0xFF,frontSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
        }

        if(spriteFlags&(1<<5)){

         reverseTile(frontSpriteBuffer,spriteX-8,spriteY-16);
        }
       } else {

        if((spriteFlags&(1<<4))==0){
         drawBGTileToBuffer(spriteTileNum&0xFF,backSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
        } else {
         drawBGTileToBuffer(spriteTileNum&0xFF,backSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
        }

        if(spriteFlags&(1<<5)){

         reverseTile(backSpriteBuffer,spriteX-8,spriteY-16);
        }
       }
      } else {

       if((spriteFlags&(1<<7))==0){

        if((spriteFlags&(1<<4))==0){
         drawBGTileToBuffer(spriteTileNum&0xFE,frontSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
         drawBGTileToBuffer((spriteTileNum&0xFE)+1,frontSpriteBuffer,spriteX-8,spriteY-8,sprite0Palette);
        } else {
         drawBGTileToBuffer(spriteTileNum&0xFE,frontSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
         drawBGTileToBuffer((spriteTileNum&0xFE)+1,frontSpriteBuffer,spriteX-8,spriteY-8,sprite1Palette);
        }

        if(spriteFlags&(1<<5)){

         reverseTile(frontSpriteBuffer,spriteX-8,spriteY-16);
         reverseTile(frontSpriteBuffer,spriteX-8,spriteY-8);
        }
       } else {

        if((spriteFlags&(1<<4))==0){
         drawBGTileToBuffer(spriteTileNum&0xFE,backSpriteBuffer,spriteX-8,spriteY-16,sprite0Palette);
         drawBGTileToBuffer((spriteTileNum&0xFE)+1,backSpriteBuffer,spriteX-8,spriteY-8,sprite0Palette);
        } else {
         drawBGTileToBuffer(spriteTileNum&0xFE,backSpriteBuffer,spriteX-8,spriteY-16,sprite1Palette);
         drawBGTileToBuffer((spriteTileNum&0xFE)+1,backSpriteBuffer,spriteX-8,spriteY-8,sprite1Palette);
        }

        if(spriteFlags&(1<<5)){

         reverseTile(backSpriteBuffer,spriteX-8,spriteY-16);
         reverseTile(backSpriteBuffer,spriteX-8,spriteY-8);
        }
       }
      }
     }
    }
   }
  }

  *backSpriteBufferComplete = 1;
  *frontSpriteBufferComplete = 1;
  *beginFillingSpriteBuffer = 0;


 }
 return 0;
}

int drawVideo(void* args){

 char backSpriteBufferComplete = 0;
 char frontSpriteBufferComplete = 0;
 char backgroundBufferComplete = 0;
 char windowBufferComplete = 0;

 char beginFillingBackgroundBuffer = 0;
 char beginFillingWindowBuffer = 0;
 char beginFillingSpriteBuffer = 0;

 SDL_Thread *backgroundBufferFillThread = ((void *)0);
 SDL_Thread *windowBufferFillThread = ((void *)0);
 SDL_Thread *spriteBufferFillThread = ((void *)0);

 void* backgroundArgs[3];
 void* windowArgs[3];
 void* spriteArgs[5];

 int i,j;

 SDL_Surface* screenBitmap = ((void *)0);

 drawBuffer backgroundBuffer;
 drawBuffer windowBuffer;
 drawBuffer backSpriteBuffer;
 drawBuffer frontSpriteBuffer;

 unsigned int currTime;
 unsigned int prevTime = 0;
 int framesElapsed = 0;

 printf("Video Thread Started!\n");


 backgroundArgs[0] = &backgroundBufferComplete;
 backgroundArgs[1] = &beginFillingBackgroundBuffer;
 backgroundArgs[2] = backgroundBuffer;

 windowArgs[0] = &windowBufferComplete;
 windowArgs[1] = &beginFillingWindowBuffer;
 windowArgs[2] = windowBuffer;

 spriteArgs[0] = &backSpriteBufferComplete;
 spriteArgs[1] = &frontSpriteBufferComplete;
 spriteArgs[2] = &beginFillingSpriteBuffer;
 spriteArgs[3] = backSpriteBuffer;
 spriteArgs[4] = frontSpriteBuffer;

 spriteStartSem = SDL_CreateSemaphore(0);
 windowStartSem = SDL_CreateSemaphore(0);
 backgroundStartSem = SDL_CreateSemaphore(0);

 spriteEndSem = SDL_CreateSemaphore(0);
 windowEndSem = SDL_CreateSemaphore(0);
 backgroundEndSem = SDL_CreateSemaphore(0);

 screenBitmap = SDL_CreateRGBSurface(0x00000000,160*1,144*1,32,0,0,0,0);
 if(screenBitmap == ((void *)0)){
  printf("Unable to create screenBuffer Exiting!!!\n");
  exit(1);
 }

 printf("Starting to create threads\n");

 backgroundBufferFillThread = SDL_CreateThread(backgroundBufferFill,backgroundArgs);
 if(backgroundBufferFillThread == ((void *)0)){
  printf("Unable to create backgroundBufferFillThread Exiting!!!\n");
  exit(1);
 }

 windowBufferFillThread = SDL_CreateThread(windowBufferFill,windowArgs);
 if(windowBufferFillThread == ((void *)0)){
  printf("Unable to create windowBufferFillThread Exiting!!!\n");
  exit(1);
 }

 spriteBufferFillThread = SDL_CreateThread(spriteBufferFill,spriteArgs);
 if(spriteBufferFillThread == ((void *)0)){
  printf("Unable to create spriteBufferFillThread Exiting!!!\n");
  exit(1);
 }

 printf("Finished creating Threads\n");





 drawingComplete=1;

 while(1){
  if(shouldFillBuffers == 1){



   backSpriteBufferComplete = 1;
   frontSpriteBufferComplete = 1;
   backgroundBufferComplete = 0;
   windowBufferComplete = 1;

   beginFillingBackgroundBuffer = 1;
   beginFillingWindowBuffer = 1;
   beginFillingSpriteBuffer = 1;
# 941 "source/video.c"
   while(backSpriteBufferComplete==0);
   while(frontSpriteBufferComplete==0);
   while(backgroundBufferComplete==0);
   while(windowBufferComplete==0);

   buffersFull = 1;
   shouldFillBuffers = 0;

  } else if(shouldRedraw == 1){




   if(SDL_LockSurface(display) == -1){
    printf("Couldn't Lock display!!!\n");
   }

   for(i=0;i<160;i++){
    for(j=0;j<144;j++){
     putPixelSDL(i,j,backgroundBuffer[i][j],display);
     if(checkForWhite(backgroundBuffer[i][j]) == 1){

      if((getAlpha(backSpriteBuffer[i][j])&0xFF) != 0xAA){

       putPixelSDL(i,j,backSpriteBuffer[i][j],display);
      }
     }



     if((getAlpha(frontSpriteBuffer[i][j])&0xFF) != 0xAA){


      putPixelSDL(i,j,frontSpriteBuffer[i][j],display);
     }
    }
   }

   SDL_UnlockSurface(display);

   SDL_Flip(display);

   if(framesElapsed == 60){
    framesElapsed = 0;
    currTime = SDL_GetTicks();

    if((currTime-prevTime)<1000){
     printf("Delaying fps\n");
     SDL_Delay(1000-(currTime-prevTime));
    } else {
     printf("fps: %f\n",60./((float)(currTime-prevTime)/1000.));
    }

    prevTime = currTime;


   } else {
    framesElapsed++;
   }


   shouldRedraw = 0;
   drawingComplete = 1;


  }

 }
}

void initVideo(){

 SDL_Thread *drawThread;

 display = SDL_SetVideoMode(160*1,144*1,32,0x00000000);
 if(display == ((void *)0)){
  printf("Display could not be created!!!\n");
  exit(0);
 }

 drawThread = SDL_CreateThread(drawVideo,((void *)0));
 if(drawThread == ((void *)0)){
  printf("Couldn't create drawThread!!!\n");
  exit(0);
 }

}
