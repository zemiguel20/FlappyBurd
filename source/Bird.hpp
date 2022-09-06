class Bird
{
private:
    Transform2D tf; // Bird transform
    Texture *tex;   // Bird texture

public:
    Bird()
    {
        tf = Transform2D(Vector2(), 0.0f, 2.0f);
        tex = new Texture("assets/burd.png");
    };
    ~Bird()
    {
        delete tex;
    };

    void Update(){};
    void Render(const Camera2D &cam)
    {
        RenderSprite(cam, tf, *tex);
    };
};