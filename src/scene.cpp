#include "scene.h"

Scene::Scene()
    : sf::Drawable()
{
}

Scene::~Scene()
{
    m_layers.clear();
}

void Scene::addLayer(Layer &layer)
{
    m_layers.push_back(&layer);
}

LayerContainer &Scene::layers()
{
    return m_layers;
}

void Scene::update(sf::Time delta)
{
    for (auto layer : m_layers)
        layer->update(delta);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto layer : m_layers)
        target.draw(*layer);
}
