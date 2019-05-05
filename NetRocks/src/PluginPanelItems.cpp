#include <utils.h>
#include "PluginPanelItems.h"

static PluginPanelItem *PluginPanelItems_ReAlloc(PluginPanelItem *prev, int capacity)
{
	size_t alloc_size = ((size_t)capacity) * sizeof(PluginPanelItem);
	if (alloc_size < (size_t)capacity)
		return nullptr;

	return (PluginPanelItem *)realloc(prev, alloc_size);
}

void PluginPanelItems_Free(PluginPanelItem *items, int count)
{
	if (items != nullptr) {
		for (int i = 0; i < count; ++i) {
			free(items[i].FindData.lpwszFileName);
		}
		free(items);
	}
}

PluginPanelItems::~PluginPanelItems()
{
	PluginPanelItems_Free(items, count);
}


void PluginPanelItems::Detach()
{
	items = nullptr;
	capacity = count = 0;
}


PluginPanelItem *PluginPanelItems::Add(const wchar_t *name) throw (std::runtime_error)
{
	if (count == capacity) {
		int new_capacity = capacity + capacity/2 + 0x100;
		if (new_capacity < capacity) {
			new_capacity = capacity + 1;
			if (new_capacity < capacity) {
				throw std::runtime_error("PluginPanelItems: capacity overflow");;
			}
		}
		PluginPanelItem *new_items = PluginPanelItems_ReAlloc(items, new_capacity);
		if (new_items == nullptr) {
			new_capacity = capacity + 1;
			new_items = PluginPanelItems_ReAlloc(items, new_capacity);
			if (new_items == nullptr) {
				throw std::runtime_error("PluginPanelItems: can't allocate new items");
			}
		}

		items = new_items;
		capacity = new_capacity;
	}

	if (count > capacity) abort();

	PluginPanelItem *out = &items[count];
	memset(out, 0, sizeof(*out));
	out->FindData.lpwszFileName = wcsdup(name);
	if (out->FindData.lpwszFileName == nullptr) {
		throw std::runtime_error("PluginPanelItems: can't allocate filename");
	}

	++count;
	return out;
}

PluginPanelItem *PluginPanelItems::Add(const char *name) throw (std::runtime_error)
{
	MB2Wide(name, _tmp);
	return Add(_tmp.c_str());
}
