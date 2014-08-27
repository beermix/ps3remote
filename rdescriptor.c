#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/hidraw.h>
#include "rdescriptor.h"


const char*
itemtag_str (unsigned char tag)
{
	unsigned char type, prefix;
	type = (tag >> 2) & 0x3;
	switch (type) {
		case TYPE_MAIN:
			prefix = (tag >> 4) & 0x7;
			return main_itemtag_strings[prefix];
		case TYPE_GLOBAL:
			prefix = (tag >> 4) & 0xf;
			return global_itemtag_strings[prefix];
		case TYPE_LOCAL:
			prefix = (tag >> 4) & 0xf;
			return local_itemtag_strings[prefix];
	}
	return reserved;
}


const char*
itemarg_str (unsigned char tag, unsigned char arg)
{
	switch (tag & 0xfa) {
		case ITEM_COLLECTION:
			if (arg > 6) {
				break;
			}
			return collection_strings[arg];
	}
	return NULL;
}


void
print_rdesc (struct hidraw_report_descriptor *rdesc)
{
	int i, num_params;
	unsigned char tag;
	uint32_t arg;
	for (i=0; i<(*rdesc).size;) {
		tag = (*rdesc).value[i++];
		arg = 0;
		num_params = tag & MASK_NUMPARAMS;
		printf("[0x%02x %s]", tag, itemtag_str(tag));
		switch (num_params) {
			case 3:
				arg |= (*rdesc).value[i++];
				arg <<= 8;
				arg |= (*rdesc).value[i++];
				arg <<= 8;
			case 2:
				arg |= (*rdesc).value[i++];
				arg <<= 8;
			case 1:
				arg |= (*rdesc).value[i++];
		}
		printf(" (0x%02x %s)", arg, itemarg_str(tag, arg));
		putchar('\n');
	}
}
