m1_dic: basic.h basic.c dic.h dic.c m1.h m1.c m1_dic.c
	gcc -std=c99 basic.c dic.c m1.c m1_dic.c -o m1_dic
m2_dic: basic.h basic.c dic.h dic.c m2.h m2.c m2_dic.c
	gcc -std=c99 basic.c dic.c m2.c m2_dic.c -o m2_dic
sbt_dic: basic.h basic.c dic.h dic.c sbt.h sbt.c sbt_dic.c
	gcc -std=c99 basic.c dic.c sbt.c sbt_dic.c -o sbt_dic
test: basic.h basic.c dic.h dic.c sbt.h sbt.c test.c m1.h m1.c m2.h m2.c
	gcc -std=c99 basic.c dic.c sbt.c test.c m1.c m2.c -o test
