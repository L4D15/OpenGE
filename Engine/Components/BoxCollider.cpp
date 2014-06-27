#include "Engine/Components/BoxCollider.hpp"

using namespace Components;

BoxCollider::BoxCollider(json_spirit::Value jsonString)
: box(0.0f, 0.0f, 0.0f, 0.0f)
{
    /*
		JSON TEMPLATE FOR BOXCOLLIDER COMPONENT
		{
			"name": "BoxCollider",
			"offset":
			{
				"x": 0.0,
				"y": 0.0
			},
			"dimensions":
			{
				"width": 1.0,
				"height": 2.0
			},
            "isTrigger": false
		}
	*/

	float x, y, w, h;

	if (jsonString.contains("offset"))
	{
		json_spirit::Value offset = jsonString.getObject().at("offset");
		x = offset.getObject().at("x").getReal();
		y = offset.getObject().at("y").getReal();
	}
	else
	{
		x = 0.0f;
		y = 0.0f;
	}

	if (jsonString.contains("dimensions"))
	{
		json_spirit::Value dimensions = jsonString.getObject().at("dimensions");
		w = dimensions.getObject().at("width").getReal();
		h = dimensions.getObject().at("height").getReal();
	}
	else
	{
		w = 0.0f;
		h = 0.0f;
	}

	box.offsetX = x;
	box.offsetY = y;
	box.width = w;
	box.height = h;
    
    if (jsonString.contains("isTrigger"))
    {
        isTrigger = jsonString.getObject().at("isTrigger").getBool();
    }
    else
    {
        isTrigger = false;
    }
}
