
import System.Exception;

public namespace System.IO {

	public object File {
		public enum AccessMode {
			Append = 0,
			AppendUpdate = 1,
			ReadOnly = 2,
			ReadUpdate = 3,
			ReadWrite = 4,
			WriteOnly = 5,
			WriteUpdate = 6;
		}

		public static bool FileExists( string filename ) {
			var handle = fopen( filename, "r" );

			if ( handle ) {
				fclose( handle );
				return true;
			}

			return false;
		}


		public void Constructor() {
			cleanup();
		}

		public void Constructor( string filename, System.IO.File.AccessMode mode const ) {
			Constructor( filename, MapFileAccessModeToString( mode ) );
		}

		public void Constructor( string filename, string mode = "r" ) {
			open( filename, mode );
		}

		public void Destructor() {
			close();
		}

		private void cleanup() modify {
			mAccessMode = "";
			mFilename = "";
			mHandle = 0;
		}

		public bool close() modify {
			if ( !mHandle ) {
				return true;
			}

			int result = fclose( mHandle );

			cleanup();

			return result == 0;
		}

		public string getAccessMode() const {
			return mAccessMode;
		}

		public string getFilename() const {
			return mFilename;
		}

		public bool isEOF() const {
			return feof( mHandle );
		}

		public bool isOpen() const {
			return mHandle != 0;
		}

		public bool open( string filename, System.IO.File.AccessMode mode const ) modify throws {
			return open( filename, MapFileAccessModeToString( mode ) );
		}

		public bool open( string filename, string mode ) modify throws {
			if ( mHandle ) {
				// we already have an open file handle
				throw new Exception( "file descriptor still points to an open file!" );
			}

			mAccessMode = mode;
			mFilename = filename;
			mHandle = fopen( mFilename, mAccessMode );

			return mHandle != 0;
		}

		public bool readBool() const {
			return freadb( mHandle );
		}

		public string readChar() const {
			return freads( mHandle, 1 );
		}

		public double readDouble() const {
			return freadd( mHandle );
		}

		public float readFloat() const {
			return freadf( mHandle );
		}

		public int readInt() const {
			return freadi( mHandle );
		}

		public string readString(int length) const {
			return freads( mHandle, length );
		}

		public bool rewind() const {
			return fseek( mHandle, 0 ) == 0;
		}

		public bool seek( int address ) {
			return fseek( mHandle, address ) == 0;
		}

		public bool write( bool value ) {
			return fwriteb( mHandle, value ) == 0;
		}

		public bool write( double value ) {
			return fwrited( mHandle, value ) == 0;
		}

		public bool write( float value ) {
			return fwritef( mHandle, value ) == 0;
		}

		public bool write( int value ) {
			return fwritei( mHandle, value ) == 0;
		}

		public bool write( string value ) {
			return fwrites( mHandle, value ) == 0;
		}

		private string mAccessMode;
		private string mFilename;
		private int mHandle;
	}

	private string MapFileAccessModeToString( System.IO.File.AccessMode mode const ) const throws {
		switch ( mode ) {
			case System.IO.File.AccessMode.Append      : { return "a"; }
			case System.IO.File.AccessMode.AppendUpdate: { return "a+"; }
			case System.IO.File.AccessMode.ReadOnly    : { return "r"; }
			case System.IO.File.AccessMode.ReadUpdate  : { return "r+"; }
			case System.IO.File.AccessMode.ReadWrite   : { return "rw"; }
			case System.IO.File.AccessMode.WriteOnly   : { return "w"; }
			case System.IO.File.AccessMode.WriteUpdate : { return "w+"; }
		}

		throw new Exception( "invalid access mode( " + cast<string>( mode ) + " ) provided!" );
	}

	private System.IO.File.AccessMode MapStringToFileAccessMode(string mode) const throws {
		switch ( mode ) {
			case "a" : { return System.IO.File.AccessMode.Append; }
			case "a+": { return System.IO.File.AccessMode.AppendUpdate; }
			case "r" : { return System.IO.File.AccessMode.ReadOnly; }
			case "r+": { return System.IO.File.AccessMode.ReadUpdate; }
			case "rw": { return System.IO.File.AccessMode.ReadWrite; }
			case "w" : { return System.IO.File.AccessMode.WriteOnly; }
			case "w+": { return System.IO.File.AccessMode.WriteUpdate; }
		}

		throw new Exception( "invalid mode( \"" + mode + "\" ) provided!" );
	}
}

