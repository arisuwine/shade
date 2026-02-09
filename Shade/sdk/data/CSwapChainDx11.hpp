#pragma once
#include "../offsets.hpp"

class IDXGISwapChain;

class CSwapChainDx11 {
public:
	SCHEMA(IDXGISwapChain*, offsets::rendersystemdx11::CSwapChainDx11::m_pDXGISwapChain, m_pDXGISwapChain);
};