/*
Dragonfire
Copyright (C) 2020 Elias Fleckenstein <eliasfleckenstein@web.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/ 

#include <vector>
#include "client/client.h"
#include "client/camera.h"
#include "tracers.h" 
#include "constants.h"

void Tracers::draw(video::IVideoDriver* driver, Client *client)
{
	ClientEnvironment &env = client->getEnv();
	LocalPlayer *player = env.getLocalPlayer();
	Camera *camera = client->getCamera();
	v3f player_pos = camera->getPosition() + camera->getDirection();
	v3f head_pos = player_pos;
	std::vector<DistanceSortedActiveObject> allObjects;
	env.getActiveObjects(player_pos, 1000000, allObjects);
	for (const auto &allObject : allObjects) {
		ClientActiveObject *obj = allObject.obj;
		if (obj->isLocalPlayer())
			continue;
		driver->draw3DLine(head_pos, obj->getPosition(), video::SColor(255, 255, 255, 255));
	}
}
