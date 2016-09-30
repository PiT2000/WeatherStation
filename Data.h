#ifndef _DATA
#define _DATA
class Data {
  public:
    String  get   ( void )        { _data += ";"; return _data; }
    void    append( float var )   { _data += String(var); _data += " "; }
    void    clear ( void )        { _data=""; }

  private:
    String _data;
};
#endif
