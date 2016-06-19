CC =    cc
CFLAGS =  -pipe -fPIC -O -W -Wall -Wpointer-arith -Wno-unused-parameter -Werror -g
CPP =   cc -E
LINK =  $(CC)

INCS = -Iinclude

DEPS = 	include/ngx_array.h 		\
		include/ngx_buf.h			\
		include/ngx_hash.h 			\
		include/ngx_list.h 			\
		include/ngx_palloc.h 		\
		include/ngx_queue.h 		\
		include/ngx_radix_tree.h 	\
		include/ngx_rbtree.h 		\
		include/ngx_string.h 		\
		include/ngx_alloc.h 		\

libnginx.so: objs/ngx_array.o 		\
			 objs/ngx_buf.o 		\
			 objs/ngx_hash.o 		\
			 objs/ngx_list.o 		\
			 objs/ngx_palloc.o 		\
			 objs/ngx_queue.o 		\
			 objs/ngx_radix_tree.o 	\
			 objs/ngx_rbtree.o 		\
			 objs/ngx_string.o 		\
			 objs/ngx_alloc.o 		\

	$(LINK) -shared -o libnginx.so 	\
			objs/ngx_array.o 		\
			objs/ngx_buf.o 			\
			objs/ngx_hash.o 		\
			objs/ngx_list.o 		\
			objs/ngx_palloc.o 		\
			objs/ngx_queue.o 		\
			objs/ngx_radix_tree.o 	\
			objs/ngx_rbtree.o 		\
			objs/ngx_string.o 		\
			objs/ngx_alloc.o 		\
			-Wl,-E

all:
	make clean
	make

install:
	mkdir /usr/local/include/libnginx
	cp -rf include/*.h /usr/local/include/libnginx/
	cp libnginx.so /usr/local/lib/

clean:
	rm -rf libnginx.so 	\
			objs/ngx_array.o 		\
			objs/ngx_buf.o 			\
			objs/ngx_hash.o 		\
			objs/ngx_list.o 		\
			objs/ngx_palloc.o 		\
			objs/ngx_queue.o 		\
			objs/ngx_radix_tree.o 	\
			objs/ngx_rbtree.o 		\
			objs/ngx_string.o 		\
			objs/ngx_alloc.o 		\

objs/ngx_array.o: $(DEPS) ngx_array.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_array.o ngx_array.c

objs/ngx_buf.o: $(DEPS) ngx_buf.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_buf.o ngx_buf.c

objs/ngx_hash.o: $(DEPS) ngx_hash.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_hash.o ngx_hash.c

objs/ngx_list.o: $(DEPS) ngx_list.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_list.o ngx_list.c

objs/ngx_palloc.o: $(DEPS) ngx_palloc.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_palloc.o ngx_palloc.c

objs/ngx_queue.o: $(DEPS) ngx_queue.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_queue.o ngx_queue.c

objs/ngx_radix_tree.o: $(DEPS) ngx_radix_tree.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_radix_tree.o ngx_radix_tree.c

objs/ngx_rbtree.o: $(DEPS) ngx_rbtree.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_rbtree.o ngx_rbtree.c

objs/ngx_string.o: $(DEPS) ngx_string.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_string.o ngx_string.c

objs/ngx_alloc.o: $(DEPS) ngx_alloc.c
	$(CC) -c $(CFLAGS) $(INCS) -o objs/ngx_alloc.o ngx_alloc.c
