# 需要判断是否存在依赖文件
objs := main.o sub.o

test : $(objs)
	gcc -o test $^

dep_files := $(foreach f, $(objs), .$(f).d)
dep_files := $(wildcard $(dep_files))

# 把依赖文件包含进来
ifneq ($(dep_files),)
	include $(dep_files)
endif

%.o : %.c
	gcc -Wp,-MD,.$@.d -c -o $@ $<
	
clean:
	rm -f *.o test
	
distclean:
	rm -f $(dep_files) *.o test
