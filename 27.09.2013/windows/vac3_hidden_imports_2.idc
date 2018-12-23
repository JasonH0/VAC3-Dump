#include <idc.idc>

static main()
{
    auto funcPtrsStart, start, currFuncPtrsStart, currStart, i, stringStart, length, currXOR, p, k, importString, prefix;
	
	funcPtrsStart = CreateArray ( "funcPtrsStart" ); // function array pointers starts
    start = CreateArray ( "start" ); // string array pointers starts
	
	SetArrayLong ( funcPtrsStart, 0, 0x10413120 );
	SetArrayLong ( funcPtrsStart, 1, 0x10413218 );
	SetArrayLong ( funcPtrsStart, 2, 0x10413250 );
	SetArrayLong ( funcPtrsStart, 3, 0x10413270 );
	SetArrayLong ( funcPtrsStart, 4, 0x10413240 );
	SetArrayLong ( funcPtrsStart, 5, 0x10413208 );
	SetArrayLong ( funcPtrsStart, 6, 0x104131EC );
	
	SetArrayLong ( start, 0, 0x1000DAC8 );
	SetArrayLong ( start, 1, 0x1000DBA4 );
	SetArrayLong ( start, 2, 0x1000DBE4 );
	SetArrayLong ( start, 3, 0x1000DC08 );
	SetArrayLong ( start, 4, 0x1000DBD0 );
	SetArrayLong ( start, 5, 0x1000DC1C );
	SetArrayLong ( start, 6, 0x1000DB8C );
	
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