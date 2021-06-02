#include "vrpch.h"
#include "layerStack.h"

namespace Variant {
	layerStack::layerStack()
	{
		m_layerit = m_layers.begin();
	}
	layerStack::~layerStack()
	{
		for (layer* layer : m_layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}
	void layerStack::pushLayer(layer* layer)
	{
		m_layers.emplace(m_layerit, layer);
		m_layerit++;
	}
	void layerStack::popLayer(layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			layer->OnDetach();
			m_layers.erase(it);
			m_layerit++;
		}
		
	}
	void layerStack::pushOverlay(layer* layer)
	{
		m_layers.emplace_back(layer);
	}
	void layerStack::popOverlay(layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			layer->OnDetach();
			m_layers.erase(it);
		}
		
	}
}
