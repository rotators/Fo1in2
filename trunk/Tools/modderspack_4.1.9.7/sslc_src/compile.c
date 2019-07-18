#define WIN32_LEAN_AND_MEAN
#define _CRT_RAND_S
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "parse.h"
#include <io.h>

int noinputwait = 0;
int warnings = 1;
int backwardcompat = 0;
int optimize = 0;
int debug = 0;
int preprocess_fullpath = 0;
int dumpTree = 0;
int shortCircuit = 0;
FILE *parseroutput;

#define FINDDATA _finddata_t
#define FINDFIRST(x, y) _findfirst(x, y)
#define FINDNEXT(x, y) _findnext(x, y)
#define FINDCLOSE(x, y) _findclose(x)
#define FINDHANDLE long
//	#define BAD_HANDLE -1

#if defined(_MSC_VER)
#define FIND_SUCCESS(x)	((x) != -1)
#else
#define FIND_SUCCESS(x)	((x) == 0)
#endif

static void PrintLogo() {
	parseOutput("Startreck scripting language compiler (Fallout 2 sfall edition 4.0)\n\n"
		"Preprocessing handled by mcpp 2.7.2\n"
		"Copyright (c) 1998, 2002-2008 Kiyoshi Matsui <kmatsui@t3.rim.or.jp>\n"
        "All rights reserved.\n\n");
}

extern int warn_level; //the mcpp warning level
extern int mcpp_lib_main(FILE *fin, FILE *fout, const char* in_file, const char* dir);
//extern void set_a_dir(const char * dirname);

#ifndef BUILDING_DLL
int main(int argc, char **argv)
{
	InputStream foo;
	char name[260], *c, *file;
	struct FINDDATA buf;
	FINDHANDLE handle;
	int nologo=0;
	int preprocess=0;
	int onlypreprocess=0;

	if (argc < 2) {
		PrintLogo();
		parseOutput("Usage: compile {switches} filename [-o outputname] [filename [..]]\n");
		parseOutput("  -q    don't wait for input on error\n");
		parseOutput("  -n    no warnings\n");
		parseOutput("  -b    use backward compatibility mode\n");
		parseOutput("  -l    no logo\n");
		parseOutput("  -p    preprocess\n");
		parseOutput("  -P    preprocess only. (Don't generate .int)\n");
		parseOutput("  -F    write full file paths in #line directives\n");
		parseOutput("  -O<level>    optimize (0 - none, 1 - only remove unreferenced globals, 2 - full, 3 - full+experimental, don't use!)\n");
		parseOutput("  -d    show debug info\n");
		parseOutput("  -s    enable short-circuit evaluation for boolean operators (AND, OR)\n");
		parseOutput("  -D    dump abstract syntax tree after optimizations\n");
		return 1;
	}

	while((argv[1] != NULL) && (argv[1][0] == '-')) {
		switch(argv[1][1]) {
		case 'w':
		case '-':
			break;
		case 'n':
			warnings=0;
			warn_level=0;
			break;
		case 'q':
			noinputwait=1;
			break;
		case 'd':
			debug=1;
			break;
		case 'b':
			backwardcompat = 1;
			break;
	    case 'l':
			nologo=1;
			break;
		case 'O':
			if (strlen(argv[1]) == 2) optimize = 2;
			else optimize = atoi(&argv[1][2]);
			break;
		case 'P':
			onlypreprocess = 1;
		case 'p':
			preprocess = 1;
			break;
		case 'F':
			preprocess_fullpath = 1;
			break;
		case 'D':
			dumpTree = 1;
			break;
		case 's':
			shortCircuit = 1;
			break;
		default:
			parseOutput("Unknown option %c\n", argv[1][1]);
		}

		argv++;
		argc--;
	}

	if(backwardcompat&&(optimize||preprocess)) {
		parseOutput("Invalid option combination; cannot run preprocess or optimization passes in backward compatibility mode\n");
		return -1;
	}

	if(!nologo) PrintLogo();

	compilerErrorTotal = 0;

	while(argv[1]) {
		file = argv[1];
		argv++;
		argc--;

		if (FIND_SUCCESS(handle = FINDFIRST(file, &buf))) {
			do {
				foo.name = AddFileName(buf.name);

				if ((foo.file = fopen(buf.name, "r")) == 0) {
					parseOutput("Couldn't find file %s\n", buf.name);
					return -1;
				}

				parseOutput("Compiling %s\n", buf.name);

				if(argc>=2&&!strcmp(argv[1], "-o")) {
					argv+=2;
					argc-=2;
					strcpy_s(name, 260, argv[0]);
				} else {
					strcpy_s(name, 260, buf.name);
					c = strrchr(name, '.');

					if (c) {
						*c = 0;
					}

					if(onlypreprocess) {
						strcat_s(name, 260, ".preprocessed.ssl");

						if (strcmp(name, buf.name) == 0) {
							c = strrchr(name, '.');
							*c = 0;
							*--c = 0;
							strcat_s(name, 260, "1.preprocessed.ssl");
						}
					} else {
						strcat_s(name, 260, ".int");

						if (strcmp(name, buf.name) == 0) {
							c = strrchr(name, '.');
							*c = 0;
							*--c = 0;
							strcat_s(name, 260, "1.int");
						}
					}
				}

				if(preprocess) {
					FILE *newfile;
					unsigned int letters;
					char tmpbuf[260];
					rand_s(&letters);
					if(onlypreprocess) {
						strcpy_s(tmpbuf, 260, name);
						newfile=fopen(tmpbuf, "w+");
					} else {
						sprintf(tmpbuf, "%d_%8x.tmp", GetCurrentProcessId(), letters);
//#if _DEBUG
//						newfile=fopen(tmpbuf, "w+");
//#else
						newfile=fopen(tmpbuf, "w+DT");
//#endif
					}
					if(mcpp_lib_main(foo.file, newfile, buf.name, buf.name)) {
						parseOutput("*** An error occured during preprocessing of %s ***\n", buf.name);
						return 1;
					}
					fclose(foo.file);
					rewind(newfile);
					foo.file=newfile;
				}
				if(!onlypreprocess) {
					parse(&foo, name);
					freeCurrentProgram();
				}
				fclose(foo.file);
				FreeFileNames();
			} while (!FINDNEXT(handle, &buf));

			FINDCLOSE(handle, &buf);

			if (compilerErrorTotal) {
				parseOutput("\n*** THERE WERE ERRORS (%u of them) ***\n", compilerErrorTotal);
				if (!noinputwait)
					getchar();
				return 1;
			}
		}
		else  {
			parseOutput("Warning: %s not found\n", file);
		}
	}
	return 0;
}
#endif

#ifdef BUILDING_DLL

static int inited=0;

int _stdcall parse_main(const char *filePath, const char* origPath, const char* dir) {
	InputStream foo;
	char tmpbuf[260];
	//char cwd[1024];
	FILE *newfile;
	unsigned int letters;

	if(inited) {
		freeCurrentProgram();
		FreeFileNames();
		inited=0;
	}

	foo.name=AddFileName(origPath);
	foo.file = fopen(filePath, "r");

	rand_s(&letters);
	sprintf(tmpbuf, "%d_%8x.tmp", GetCurrentProcessId(), letters);
	newfile=fopen(tmpbuf, "w+DT");
	//newfile=fopen(tmpbuf, "w+");
	parseroutput = fopen("errors.txt", "w");
	//GetCurrentDirectoryA(1024, cwd);
	//chdir(dir);
	compilerErrorTotal = 0;
	preprocess_fullpath = 1;
	if (mcpp_lib_main(foo.file, newfile, origPath, dir)) {
		fclose(foo.file);
		fclose(newfile);
		if (parseroutput)
			fclose(parseroutput);
		return 2;
	}
	//chdir(cwd);

	fclose(foo.file);
	//fflush(newfile);
	rewind(newfile);
	foo.file=newfile;
	parse(&foo, NULL);
	fclose(foo.file);

	inited=1;
	if (parseroutput)
		fclose(parseroutput);
	if (compilerErrorTotal) {
		return 1;
	}
	return 0;
}

#endif
