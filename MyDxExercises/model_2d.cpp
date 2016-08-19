#include "model_2d.h"

const int vertex_length = 30;

Model2D::Model2D()
	: m_arr_vertex(NULL)
	, m_vbuffer(NULL)
	, m_ibuffer(NULL)
{

}

Model2D::~Model2D()
{
	UnloadFromRam();
}

void Model2D::Render()
{
	g_d3ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_d3ddevice->SetStreamSource(0, m_vbuffer, 0, sizeof(VertexStruct));
	g_d3ddevice->SetFVF(VertexFVF);
	g_d3ddevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, vertex_length / 3 );
}

bool Model2D::LoadToRam()
{
	UnloadFromRam();
	
	m_arr_vertex = new VertexStruct[vertex_length];
	ZeroMemory( m_arr_vertex, sizeof(VertexStruct) * vertex_length );

	for( int i = 0; i < vertex_length; ++i )
	{
		(m_arr_vertex + i)->x = (rand()%2)? 0 : (g_screen_width-1);
		(m_arr_vertex + i)->y = (rand()%2)? 0 : (g_screen_height-1);
		(m_arr_vertex + i)->z = 1.0f;
		(m_arr_vertex + i)->rhw = 1.0f;
		(m_arr_vertex + i)->color = 0x0000ff;
	}
	//(m_arr_vertex + 0)->x = 150.0f,  (m_arr_vertex + 0)->y = 50.0f, (m_arr_vertex + 0)->z = 0.5f, (m_arr_vertex + 0)->rhw = 1.0f, (m_arr_vertex + 0)->color = 0xffff0000; // x, y, z, rhw, color
	//(m_arr_vertex + 1)->x = 250.0f,  (m_arr_vertex + 1)->y = 250.0f, (m_arr_vertex + 1)->z = 0.5f, (m_arr_vertex + 1)->rhw = 1.0f, (m_arr_vertex + 1)->color = 0xffff0000; // x, y, z, rhw, color
	//(m_arr_vertex + 2)->x = 50.0f,  (m_arr_vertex + 2)->y = 250.0f, (m_arr_vertex + 2)->z = 0.5f, (m_arr_vertex + 2)->rhw = 1.0f, (m_arr_vertex + 2)->color = 0xffff0000; // x, y, z, rhw, color

	return true;
}

void Model2D::UnloadFromRam()
{
	UnloadFromBuffer();

	if( m_arr_vertex )
	{
		delete[] m_arr_vertex;
		m_arr_vertex = NULL;
	}
}

bool Model2D::LoadToBuffer()
{
	if( FAILED(g_d3ddevice->CreateVertexBuffer(sizeof(VertexStruct) * vertex_length, 0, VertexFVF, D3DPOOL_DEFAULT, &m_vbuffer, NULL)) )
		return false;

	VOID* pData;
	if( FAILED(m_vbuffer->Lock(0, sizeof(VertexStruct) * vertex_length, &pData, 0)) )
		return false;

	memcpy(pData, m_arr_vertex, sizeof(VertexStruct) * vertex_length);
	m_vbuffer->Unlock();

	return true;
}

void Model2D::UnloadFromBuffer()
{
	if( m_vbuffer )
	{
		m_vbuffer->Release();
		m_vbuffer = NULL;
	}
	if( m_ibuffer )
	{
		m_ibuffer->Release();
		m_ibuffer = NULL;
	}
}