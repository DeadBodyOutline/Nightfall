#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.hpp>

#include "layer.h"

typedef std::vector<Layer *> LayerContainer;

// XXX this class is pretty similar to Layers; check if can we us use templates
class Scene : public sf::Drawable
{
public:
    Scene();
    ~Scene();

    void addLayer(Layer &layer);
    LayerContainer &layers();

    void update(sf::Time delta = sf::Time::Zero);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    LayerContainer m_layers;
};

#endif // __SCENE_H__
