
import Settings;


public object CurlRequest {
    public void Constructor( string url = "" ) {
        mHandle = curl_init();
        mSettings = new Settings();
        mURL = url;
    }

    public void Destructor() {
        curl_cleanup( mHandle );
    }

    public string execute( string url = "" ) modify {
        if ( mSettings.UseAuthentication ) {
            curl_set_password( mHandle, mSettings.Password );
            curl_set_username( mHandle, mSettings.Username );
        }

        curl_set_progress( mHandle, mSettings.ShowProgress );
        curl_set_url( mHandle, url ?: mURL );
        curl_set_verbose( mHandle, mSettings.VerboseOutput );

        mLastError = curl_perform( mHandle );
        if ( mLastError ) {
            return "";
        }

        return curl_read_result( mHandle );
    }

    public int lastError() const {
        return mLastError;
    }

    public void setBearer( string bearer) modify {
        curl_set_bearer( mHandle, bearer );
    }

    public void setData( string data ) modify {
        curl_set_data( mHandle, data );
    }

    public void setHeader( string header) modify {
        curl_set_header( mHandle, header );
    }

    public void setOption( int option, int value ) modify {
        curl_set_opt_int( mHandle, option, value );
    }

    public void setOption( int option, string value ) modify {
        curl_set_opt_str( mHandle, option, value );
    }

    public Settings settings() const {
        return mSettings;
    }

    private int mHandle const;
    private int mLastError;
    private Settings mSettings;
    private string mURL;
}

