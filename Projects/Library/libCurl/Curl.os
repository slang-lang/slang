
import Settings;


public object Curl {
    public void Constructor( string url = "" ) {
        base.Constructor();

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
        if ( !mLastError ) {
            return curl_read_result( mHandle );
        }

        return "";
    }

    public int lastError() const {
        return mLastError;
    }

    public Settings settings() const {
        return mSettings;
    }

    private int mHandle;
    private int mLastError;
    private Settings mSettings;
    private string mURL;
}