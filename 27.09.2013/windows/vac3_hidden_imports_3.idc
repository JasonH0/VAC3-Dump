#include <idc.idc>

static main()
{
    auto funcPtrsStart, start, currFuncPtrsStart, currStart, i, stringStart, length, currXOR, p, k, importString, prefix;
	
	funcPtrsStart = CreateArray ( "funcPtrsStart" ); // function array pointers starts
    start = CreateArray ( "start" ); // string array pointers starts
	
	SetArrayLong ( funcPtrsStart, 0, 0x104131B8 );
	SetArrayLong ( funcPtrsStart, 1, 0x104132B0 );
	SetArrayLong ( funcPtrsStart, 2, 0x104132E8 );
	SetArrayLong ( funcPtrsStart, 3, 0x10413308 );
	SetArrayLong ( funcPtrsStart, 4, 0x104132D8 );
	SetArrayLong ( funcPtrsStart, 5, 0x104132A0 );
	SetArrayLong ( funcPtrsStart, 6, 0x10413284 );
	
	SetArrayLong ( start, 0, 0x1000DB20 );
	SetArrayLong ( start, 1, 0x1000DBFC );
	SetArrayLong ( start, 2, 0x1000DC3C );
	SetArrayLong ( start, 3, 0x1000DC60 );
	SetArrayLong ( start, 4, 0x1000DC28 );
	SetArrayLong ( start, 5, 0x1000DC74 );
	SetArrayLong ( start, 6, 0x1000DBE4 );
	
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