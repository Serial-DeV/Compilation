
void main()
{
	int k = 15;
	int l = 15;
	int n = 12;
	bool o = true;
	bool p = true;

	if(p != o)
	{
		int k = 10;
		print("test 1 vrai\n");
		print(k);
		print("\n");
		int c = 0;
		bool b = true;

		while(n < 2 * k)
		{
			n = n + 1;
			b = !b;
			c = c + 1;
			print(c);
			print("\n");
			print(b);
			print("\n");
			print(n);
			print("\n");
			if(b)
			{
				int l = 458;
				c = c * c;
				print(l);
				print("\n");
			}
		}
		
	}
	
	else
	{
		print("test 1 faux\n");
	}
	
	if(k < 12+1)
	{
		int o = 50;
		print("test 2 vrai\n");
		print(o);
	}
	
	else
	{
		int i;
		for(i = 0; i < 10; i = i + 1)
		{
			print(i);
			print("\n");
			print("test 2 faux\n");
		}
	}

	
	print(o);
	print("\n");
}
