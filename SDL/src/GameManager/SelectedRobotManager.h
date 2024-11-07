#pragma once
#include <string>

class SelectedRobotManager {
public:
    static void SetSelectedRobot1Texture(const std::string& texture) {
        m_selectedRobot1Texture = texture;
    }

    static const std::string& GetSelectedRobot1Texture() {
        return m_selectedRobot1Texture;
    }

    static void SetSelectedRobot2Texture(const std::string& texture) {
        m_selectedRobot2Texture = texture;
    }

    static const std::string& GetSelectedRobot2Texture() {
        return m_selectedRobot2Texture;
    }
private:
    static std::string m_selectedRobot1Texture; 
    static std::string m_selectedRobot2Texture;
};

