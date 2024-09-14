lexer grammar CSVLexer;

TXT_BLOCK_START : '"' -> skip, pushMode(TXT_BLOCK);

SEP     : [;,|?] -> skip;
NEWLINE : [\r\n]+;
CONTENT : ~[\r\n;|,"?]+;


mode TXT_BLOCK;
TXT_BLOCK_END : '"' -> skip, popMode;
TEXT_BLOCK: ~["]+;
