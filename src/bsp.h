#pragma once

#include "math.h"
#include "quadblock.h"

#include <vector>

enum class NodeType
{
	BRANCH = 0,
	LEAF = 1
};

enum class AxisSplit
{
	NONE, X, Y, Z
};

enum class BSPFlags : uint16_t
{
	NONE = 0,
	LEAF = 1 << 0,
	WATER = 1 << 1,
	SUBDIV_4_1 = 1 << 3,
	SUBDIV_4_2 = 1 << 4,
	HIDDEN = 1 << 6,
	NO_COLLISION = 1 << 7,
};

class BSP
{
public:
	BSP();
	BSP(NodeType type, const std::vector<size_t>& quadblockIndexes);
	size_t Id() const;
	bool Empty() const;
	size_t Size() const;
	bool IsBranch() const;
	const std::string& GetType() const;
	const std::string& GetAxis() const;
	const BoundingBox& GetBoundingBox() const;
	const std::vector<size_t>& GetQuadblockIndexes() const;
	const BSP* GetLeftChildren() const;
	const BSP* GetRightChildren() const;
	void SetQuadblockIndexes(const std::vector<size_t>& quadblockIndexes);
	void Clear();
	void Generate(const std::vector<Quadblock>& quadblocks, const size_t maxQuadsPerLeaf);
	std::vector<uint8_t> Serialize(size_t offQuads) const;

private:
	float GetAxisMidpoint(const AxisSplit axis) const;
	void ComputeBoundingBox(const std::vector<Quadblock>& quadblocks);
	float Split(std::vector<size_t>& left, std::vector<size_t>& right, const AxisSplit axis, const std::vector<Quadblock>& quadblocks) const;
	void GenerateOffspring(std::vector<size_t>& left, std::vector<size_t>& right, const std::vector<Quadblock>& quadblocks, const size_t maxQuadsPerLeaf);
	std::vector<uint8_t> SerializeBranch() const;
	std::vector<uint8_t> SerializeLeaf(size_t offQuads) const;

private:
	size_t m_id;
	NodeType m_type;
	AxisSplit m_axis;
	BSPFlags m_flags;
	BSP* m_left;
	BSP* m_right;
	BoundingBox m_bbox;
	std::vector<size_t> m_quadblockIndexes;
};
