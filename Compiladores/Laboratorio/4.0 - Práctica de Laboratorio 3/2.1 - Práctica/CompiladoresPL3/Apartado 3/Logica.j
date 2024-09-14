.class public Logica
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
   .limit stack 100
   .limit locals 100

   getstatic java/lang/System/out Ljava/io/PrintStream;
ldc 1
ldc 0
ior
   invokevirtual java/io/PrintStream/println(I)V
return

.end method