#pragma once
#include "layer.h"

namespace Variant {
	class layerStack
	{		
		std::vector<layer*> m_layers;
		std::vector<layer*>::iterator m_layerit;
	public:
		layerStack();
		~layerStack();
		void pushLayer(layer* layer);
		void popLayer(layer* layer);
		void pushOverlay(layer* layer);
		void popOverlay(layer* layer);

		std::vector<layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<layer*>::iterator end() { return m_layers.end(); }
		std::vector<layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<layer*>::reverse_iterator rend() { return m_layers.rend(); }

	};
}
