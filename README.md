# EmotiAgent - AI-Powered Emotional Intelligence for Hardware Agents

EmotiAgent is an innovative open-source project that brings emotional intelligence to hardware-based AI agents through the integration of Large Language Models (LLM). This project combines hardware implementations, backend processing, and frontend monitoring to create a comprehensive system for emotional expression and analysis.

## 🌟 Features

- Real-time emotion processing and expression through hardware
- LLM-powered emotional intelligence
- Advanced emotion monitoring and visualization
- Hardware-software integration for realistic emotional responses
- Comprehensive emotion tracking and analysis

## 🏗 Project Structure

The project consists of three main components:

### 1. Hardware Component

The hardware implementation enables physical expression of emotions through:

- Multiple emotion displays (angry, happy, sad, etc.)
- Display configurations for ST7735/ST7789
- Bluetooth and WiFi connectivity
- MPU integration for physical responses
- MQTT communication for real-time updates
- OTA update capability

Key features:
- Real-time emotion expression
- Multiple emotional states visualization
- Sensor integration for environmental awareness
- Wireless connectivity for remote control
- Easy firmware updates through OTA

### 2. Backend Component

The backend system processes emotions and manages AI agent behavior:

- Integration with LLM models for emotional processing
- MCP (Model Context Protocol) implementation
- Real-time emotion state management
- Hardware communication protocols
- Data processing and analysis

Key capabilities:
- Advanced emotion processing algorithms
- Real-time LLM integration
- Scalable architecture for multiple agents
- Robust API endpoints for frontend integration
- Secure communication protocols

### 3. Frontend Component

The frontend provides a comprehensive interface for:

- Real-time emotion tracking and monitoring
- Interactive data visualization
- Hardware status monitoring
- Historical emotion data analysis
- User configuration interface

Features:
- Interactive emotion graphs and charts
- Real-time hardware status updates
- Customizable monitoring dashboards
- Historical data analysis tools
- User-friendly configuration interface

## 🚀 Getting Started

### Prerequisites

- PlatformIO for hardware development
- Node.js and pnpm for backend/frontend
- Compatible hardware components (ESP32 recommended)
- Development environment setup for embedded systems

### Installation

1. Clone the repository:
```bash
git clone https://github.com/AIPEAQ-Labs/EmotiAgent.git
cd emotiagent
```

2. Hardware Setup:
```bash
cd hardware
pio run # Build the firmware
pio run --target upload # Upload to device
```

3. Backend Setup:
```bash
cd backend
pnpm install
pnpm run dev
```

4. Frontend Setup:
```bash
cd frontend
pnpm install
pnpm run dev
```

## 📖 Documentation

### Hardware Configuration

The hardware component supports various displays and sensors:
- ST7735/ST7789 display configurations
- MPU integration for movement detection
- Bluetooth/WiFi connectivity options
- SPIFFS for local storage
- I2S for audio processing

### Backend Architecture

The backend system is designed with:
- RESTful API endpoints
- WebSocket support for real-time updates
- MCP integration for AI model communication
- Scalable microservices architecture
- Robust error handling and logging

### Frontend Interface

The frontend provides:
- Real-time emotion monitoring
- Interactive data visualization
- Hardware configuration interface
- Historical data analysis
- User management system

## 🤝 Contributing

We welcome contributions! Please follow these steps:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Thanks to all contributors who have helped shape this project
- Special thanks to the open-source community for their valuable tools and libraries
- Appreciation to all users who provide feedback and suggestions

## 📞 Contact

For questions, suggestions, or collaborations, please open an issue in the repository or contact the maintainers.

---

Made with ❤️ by the AIPEAQ Labs Team
