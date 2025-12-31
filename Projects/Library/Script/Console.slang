
// library imports

// project imports


public namespace Console
{

    public enum Color
    {
        Black = 0,
        Red   = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4,
        Magenta = 5,
        Cyan = 6,
        White = 7,
        NotUsed = 8,
        Reset = 9
    }

    public void Echo( string text )
    {
        write( system( streval( "tput {{{TextMode}}}; tput setab {{{TextBackground}}}; tput setaf {{{TextColor}}}; echo '{{{text}}}'" ) ) );
    }

    public void Reset()
    {
        TextBackground = Color.Black;
        TextColor      = Color.White;
        TextMode       = "sgr0";
    }

    public void SetBackgroundColor( Color color )
    {
        system( streval( "tput setab {{{color}}}" ) );
    }

    public void SetTextBold()
    {
        TextMode = "bold";
    }

    public void SetTextColor( Color color )
    {
        TextColor = color;
    }

    public void SetTextUnderline( bool on = true )
    {
        if ( on )
            system( "tput smul" )
        else
            system( "tput rmul" );
    }

    public void SetTextDefault()
    {
        system( "tput sgr0" );
    }

    private Color  TextBackground;
    private Color  TextColor;
    private string TextMode = "sgr0";
}

