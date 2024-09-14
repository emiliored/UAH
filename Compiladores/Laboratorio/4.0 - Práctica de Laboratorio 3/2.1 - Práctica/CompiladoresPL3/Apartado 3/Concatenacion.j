.class public Concatenacion
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
   .limit stack 100
   .limit locals 100
   
   ; Define a string and a number
   .var 0 is myString:Ljava/lang/String;
   .var 1 is myNumber:I
   
   ; Assign values to the string and number
   ldc "Hello"
   astore_0
   ldc 5
   istore_1

   ; Convert the number to a string
   iload_1
   invokestatic java/lang/Integer.toString(I)Ljava/lang/String;

   ; Concatenate the string and the number
   aload_0
   invokestatic java/lang/String.concat(I)Ljava/lang/String;

   ; Print the concatenated string
   getstatic java/lang/System.out Ljava/io/PrintStream;
   invokevirtual java/io/PrintStream.println(Ljava/lang/String;)V

return

.end method