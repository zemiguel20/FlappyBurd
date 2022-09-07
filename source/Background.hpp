class Background
{
private:
    Transform2D tf;
    Texture *tex;

public:
    Background()
    {
        tf = Transform2D();
        tf.scale = 0.6f;
        tex = new Texture("assets/background-day.png");
    }

    ~Background()
    {
        delete tex;
    }

    void Render(const Camera2D &cam)
    {
        RenderSprite(cam, tf, *tex);
    }
};