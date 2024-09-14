.class public Main 
.super java/lang/Object

;
; standard initializer (calls java.lang.Object's initializer)
;
.method public <init>()V
    aload_0
    invokenonvirtual java/lang/Object/<init>()V
    return
.end method

;
; main() - prints out Hello World
;
.method public static main([Ljava/lang/String;)V
    .limit stack 32   ; up to two items can be pushed
    new java/lang/Integer
    dup
    ldc 20
    invokespecial java/lang/Integer/<init>(I)V
    invokevirtual java/lang/Integer/floatValue()F

    new java/lang/Integer
    dup
    ldc 10
    invokespecial java/lang/Integer/<init>(I)V
    invokevirtual java/lang/Integer/floatValue()F
    if_icmplt unique_l0
    ldc 0
    goto unique_l1
    unique_l0:
    ldc 1
    unique_l1:
    istore_0

    new java/lang/StringBuilder
    dup
    invokespecial java/lang/StringBuilder/<init>()V
        
    iload_0
    invokestatic java/lang/Integer/toString(I)Ljava/lang/String;
    invokevirtual java/lang/StringBuilder/append(Ljava/lang/String;)Ljava/lang/StringBuilder;
    invokevirtual java/lang/StringBuilder/toString()Ljava/lang/String;
    astore_0

    ; push System.out onto the stack
    getstatic java/lang/System/out Ljava/io/PrintStream;

    ; push a string onto the stack
    aload_0

    ; call the PrintStream.println() method.
    invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V

    ; done
    return
.end method
