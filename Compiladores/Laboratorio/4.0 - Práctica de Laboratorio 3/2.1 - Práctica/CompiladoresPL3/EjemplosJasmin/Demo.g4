grammar Demo;

addition: left=addition '+' right=NUMBER #Plus
		| number=NUMBER #Number
		;

NUMBER: [0-9]+;