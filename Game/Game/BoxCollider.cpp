#include "BoxCollider.h"
#include "GameObject.h"

//Constructor with values to be added for a Collider to be created
BoxCollider::BoxCollider(const sf::Transformable& transform, sf::Vector2f originOffset, sf::Vector2f scaleOffset) : Collider(transform), originOffset(originOffset), scaleOffset(scaleOffset) {
	
}

//Destructor
BoxCollider::~BoxCollider() {

}

//Override Start method from base Component class
void BoxCollider::Start() {
	Collider::Start();	

}

//Override Update method from base Component class
void BoxCollider::Update(float deltaTime) {
	Collider::Update(deltaTime);

	//Switch on the colliding type
	switch (GetColliderObjectType()) {
	case ColliderObjectType::Sprite:
		//Set box collider size, scale and position depending on the sprite casted object
		boxCollider.setSize(sf::Vector2f(GetSpriteCast().getLocalBounds().width, GetSpriteCast().getLocalBounds().height));
		boxCollider.setScale(GetSpriteCast().getScale() + scaleOffset);
		boxCollider.setPosition(GetSpriteCast().getPosition());
		boxCollider.setOrigin(GetSpriteCast().getOrigin() + originOffset);
		boxCollider.setRotation(GetSpriteCast().getRotation());
		break;
	case ColliderObjectType::Text:
		//Set box collider size, scale and position depending on the text casted object
		boxCollider.setSize(sf::Vector2f(GetTextCast().getGlobalBounds().width, GetTextCast().getLocalBounds().height));
		boxCollider.setScale(GetTextCast().getScale() + scaleOffset);
		boxCollider.setPosition(GetTextCast().getPosition());
		boxCollider.setOrigin(GetTextCast().getOrigin() + originOffset);
		boxCollider.setRotation(GetTextCast().getRotation());
		break;
	}
	sf::IntRect  r = boxCollider.getTextureRect();
	r.top = boxCollider.getPosition().x;
	r.left = boxCollider.getPosition().y;
	r.width = boxCollider.getSize().x;
	r.height = boxCollider.getSize().y;
	boxCollider.setTextureRect(r);
	
}

//Collide method that returns the Collider that is colliding with this object when in the begin overlap state
Collider* BoxCollider::OnBeginOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If BeginOverlap of Colliding object is false
			if (!it->second->BeginOverlap) {
				//If the objects intersect with each other return the intersecting object and set BeginOverlap value of that Collider object
				if (boxCol->CheckBoundingBox(GetBoxCollider(), boxCol->GetBoxCollider())) {
					it->second->BeginOverlap = true;
					return it->first;
				}
			}	
			else {
				//If the objects don't intersect with each set BeginOverlap value of that Collider object
				if (!boxCol->CheckBoundingBox(GetBoxCollider(), boxCol->GetBoxCollider())) {
					it->second->BeginOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

//Collide method that returns the Collider that is colliding with this object when in the stay overlap state
Collider* BoxCollider::OnStayOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If the objects intersect with each other return the intersecting object
			if (boxCol->CheckBoundingBox(GetBoxCollider(), boxCol->GetBoxCollider())) {
				return it->first;
			}
		}
	}

	return nullptr;
}

//Collide method that returns the Collider that is colliding with this object when in the end overlap state
Collider* BoxCollider::OnEndOverlap() {
	//For every collider object in the collider object map
	for (auto it = CollideableObjects.begin(); it != CollideableObjects.end(); it++) {
		//try to cast to BoxCollider;
		BoxCollider* boxCol = dynamic_cast<BoxCollider*>(it->first);

		if (boxCol) {
			//If EndOverlap of Colliding object is false
			if (!it->second->EndOverlap) {
				//If the objects don't intersect with each other return the intersecting object and set EndOverlap value of that Collider object
				if (!boxCol->CheckBoundingBox(GetBoxCollider(), boxCol->GetBoxCollider())) {
					it->second->EndOverlap = true;
					return it->first;
				}
			}
			else {
				//If the objects intersect with each set EndOverlap value of that Collider object
				if (boxCol->CheckBoundingBox(GetBoxCollider(), boxCol->GetBoxCollider())) {
					it->second->EndOverlap = false;
					return nullptr;
				}
			}
		}
	}

	return nullptr;
}

bool BoxCollider::OnMouseEnter() {
	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	if (!isMouseOverlapping) {
		if (boxCollider.getGlobalBounds().contains(mousePos)) {
			isMouseOverlapping = true;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (!boxCollider.getGlobalBounds().contains(mousePos)) {
			isMouseOverlapping = false;
			return false;
		}
		else {
			return false;
		}
	}
}

bool BoxCollider::OnMouseDown(sf::Mouse::Button mouseButton) {
	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	if (boxCollider.getGlobalBounds().contains(mousePos)) {
		isMouseDown = true;
	}
	if(OnMouseExit() && Input::GetMouseKeyUp(mouseButton)) {
		isMouseDown = false;
	}

	if (Input::GetMouseKeyDown(mouseButton) && isMouseDown) {
		return true;
	}
	if (!isMouseDown) {
		return false;
	}
	if (Input::GetMouseKeyUp(mouseButton)) {
		isMouseDown = false;
		return false;
	}
}

bool BoxCollider::OnMouseExit() {
	//Get the mouse position
	const sf::Vector2f mousePos = sf::Vector2f(Input::GetMousePosition().x, Input::GetMousePosition().y);

	if (isMouseOverlapping) {
		if (!boxCollider.getGlobalBounds().contains(mousePos)) {
			isMouseOverlapping = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (boxCollider.getGlobalBounds().contains(mousePos)) {
			isMouseOverlapping = true;
			return false;
		}
		else {
			return false;
		}
	}
}

//Gets the box collider
sf::RectangleShape& BoxCollider::GetBoxCollider() {
	return boxCollider;
}

bool BoxCollider::CheckBoundingBox(const sf::RectangleShape & Object1, const sf::RectangleShape & Object2) {
	OrientedBoundingBox OBB1(Object1);
	OrientedBoundingBox OBB2(Object2);

	// Create the four distinct axes that are perpendicular to the edges of the two rectangles
	sf::Vector2f Axes[4] = {
		sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
		OBB1.Points[1].y - OBB1.Points[0].y),
		sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
		OBB1.Points[1].y - OBB1.Points[2].y),
		sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
		OBB2.Points[0].y - OBB2.Points[3].y),
		sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
		OBB2.Points[0].y - OBB2.Points[1].y)
	};

	for (int i = 0; i<4; i++) // For each axis...
	{
		float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

		// ... project the points of both OBBs onto the axis ...
		OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
		OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

		// ... and check whether the outermost projected points of both OBBs overlap.
		// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
		if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
			return false;
	}
	return true;
}
