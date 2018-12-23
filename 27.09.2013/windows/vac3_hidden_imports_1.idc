#include <idc.idc>

static main()
{
    auto funcPtrsStart, start, currFuncPtrsStart, currStart, i, stringStart, length, currXOR, p, k, importString, prefix;
	
	funcPtrsStart = CreateArray ( "funcPtrsStart" ); // function array pointers starts
    start = CreateArray ( "start" ); // string array pointers starts
	
	SetArrayLong ( funcPtrsStart, 0, 0x10412170 );
	SetArrayLong ( funcPtrsStart, 1, 0x10412268 );
	SetArrayLong ( funcPtrsStart, 2, 0x104122A0 );
	SetArrayLong ( funcPtrsStart, 3, 0x104122C0 );
	SetArrayLong ( funcPtrsStart, 4, 0x10412290 );
	SetArrayLong ( funcPtrsStart, 5, 0x10412258 );
	SetArrayLong ( funcPtrsStart, 6, 0x1041223C );
	
	SetArrayLong ( start, 0, 0x1000CB20 );
	SetArrayLong ( start, 1, 0x1000CBFC );
	SetArrayLong ( start, 2, 0x1000CC3C );
	SetArrayLong ( start, 3, 0x1000CC60 );
	SetArrayLong ( start, 4, 0x1000CC28 );
	SetArrayLong ( start, 5, 0x1000CC74 );
	SetArrayLong ( start, 6, 0x1000CBE4 );
	
	for ( i = 0; i < 7; i++ )
	{
		currFuncPtrsStart = GetArrayElement ( AR_LONG, funcPtrsStart, i );
		currStart = GetArrayElement ( AR_LONG, start, i );
		
		while ( Dword ( currStart ) )
		{
			currXOR = 0x55;
			
			p = Dword ( currStart );
			
			stringStart = p + 1;
			
			length = currXOR ^ Byte ( p );
			
			// print ( "loop " + currStart );
			
			if ( length != 0 )
			{
				PatchByte ( p, 0x55 );
				
				while ( length )
				{
					p++;
					
					k = Byte ( p );
					
					PatchByte ( p, currXOR ^ k );
					// PatchByte ( p + 1, 0x00 );
					
					length--;
					
					currXOR = k;
				}
			}
					
			MakeStr ( stringStart, BADADDR );
			
			importString = GetString ( stringStart, -1, GetStringType ( stringStart ) );
			
			MakeDword ( currFuncPtrsStart );
			
			prefix = "_";
			while ( MakeName ( currFuncPtrsStart, prefix + importString ) == 0 )
				prefix = prefix + "_";
			
			print ( "Renamed global pointer to " + prefix + importString );
			
			currFuncPtrsStart = currFuncPtrsStart + 4;
			currStart = currStart + 4;
		}
	}
}