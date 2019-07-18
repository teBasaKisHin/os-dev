; naskfunc

[FORMAT "WCOFF"]
[BITS 32]


; オブジェクトファイルのための情報

[FILE "naskfunc.nas"]

        GLOBAL	_io_hlt

; 関数の実体

[SECTION .text]

_io_hlt:	; void io_hlt(void);
		HLT
		RET
