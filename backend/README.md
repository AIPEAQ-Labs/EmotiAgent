# EmotiAgent Backend

The backend component of EmotiAgent handles emotion processing, AI integration, and hardware communication through the Model Context Protocol (MCP).

## 🚀 Features

- LLM integration for advanced emotion processing
- Real-time emotion state management
- MCP implementation for AI model communication
- Hardware communication protocols
- WebSocket support for real-time updates
- RESTful API endpoints
- Scalable microservices architecture

## 🛠 Tech Stack

- Node.js
- TypeScript
- WebSocket
- MCP (Model Context Protocol)
- RESTful APIs
- MQTT for hardware communication

## 📦 Installation

1. Install dependencies:
```bash
pnpm install
```

2. Set up environment variables:
```bash
cp .env.example .env
# Edit .env with your configuration
```

3. Start the development server:
```bash
pnpm run dev
```

## 🔧 Configuration

The backend can be configured through environment variables:

- `PORT`: Server port (default: 3000)
- `MQTT_BROKER`: MQTT broker URL
- `LLM_API_KEY`: API key for LLM service
- `MCP_CONFIG`: MCP configuration settings

## 📚 API Documentation

### Emotion Processing Endpoints

```typescript
POST /api/emotions/process
- Process emotions using LLM
- Returns processed emotion state

GET /api/emotions/current
- Get current emotion state
- Returns current emotion data

POST /api/emotions/update
- Update emotion state
- Broadcasts to connected hardware
```

### Hardware Communication

```typescript
POST /api/hardware/connect
- Register new hardware device
- Establishes WebSocket connection

POST /api/hardware/command
- Send command to hardware
- Updates hardware state
```

### MCP Integration

```typescript
POST /api/mcp/tools
- Execute MCP tools
- Returns tool execution results

GET /api/mcp/resources
- Get available MCP resources
- Returns resource list
```

## 🧪 Testing

Run the test suite:

```bash
pnpm test
```

Run tests in watch mode:

```bash
pnpm test:watch
```

## 🔍 Monitoring

The backend includes monitoring endpoints:

- `/health`: Health check endpoint
- `/metrics`: Prometheus metrics
- `/debug`: Debug information (development only)

## 📖 Development

### Code Structure

```
src/
├── api/          # API routes and controllers
├── services/     # Business logic
├── models/       # Data models
├── config/       # Configuration
├── utils/        # Utilities
└── tests/        # Test files
```

### Development Commands

```bash
pnpm run dev         # Start development server
pnpm run build       # Build for production
pnpm run start       # Start production server
pnpm run lint        # Run linter
pnpm run format      # Format code
```

## 🤝 Contributing

1. Follow the main project's contributing guidelines
2. Ensure all tests pass
3. Add tests for new features
4. Update documentation as needed

## 📝 License

This project is licensed under the MIT License - see the main project's LICENSE file for details.
