#include <vector>

class ScrollingGround
{
private:
    Texture *tex;
    std::vector<Transform2D> blocksTf;

public:
    ScrollingGround()
    {
        tex = new Texture("assets/dirtsprite.png");

        Transform2D base;
        base.scale = 1.5f;
        // Set base at bottom-left corner
        base.position.x =
            -(Config::REF_SCREEN_W / 2) +
            tex->Width() / 2 * base.scale;
        base.position.y =
            -(Config::REF_SCREEN_H / 2) +
            tex->Height() / 2 * base.scale;

        blocksTf = {base, base, base, base, base, base};

        // Set one after another
        for (int i = 0; i < blocksTf.size(); i++)
            blocksTf[i].position.x += i * tex->Width() * base.scale;

        Log::Info("Scrolling Ground loaded");
    };

    ~ScrollingGround()
    {
        blocksTf.clear();
        delete tex;
        Log::Info("Scrolling Ground unloaded");
    };

    void Update()
    {
        // Move ground
        for (Transform2D &tf : blocksTf)
        {
            tf.position.x -= Config::SCROLL_VEL * Time::DeltaTime();
        }
        // Check to move first block to the back
        bool firstNotVisible =
            blocksTf[0].position.x <
            -(Config::REF_SCREEN_W / 2) - tex->Width() / 2 * blocksTf[0].scale;
        if (firstNotVisible)
        {
            Transform2D block = blocksTf[0];
            block.position.x = blocksTf.back().position.x +
                               tex->Width() * block.scale;
            blocksTf.erase(blocksTf.begin());
            blocksTf.push_back(block);
        }
    };

    void Render(const Camera2D &cam)
    {
        for (Transform2D &tf : blocksTf)
            RenderSprite(cam, tf, *tex);
    };
};