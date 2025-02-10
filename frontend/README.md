# EmotiAgent Frontend

The frontend component of EmotiAgent provides an intuitive interface for monitoring and analyzing AI agent emotions through interactive visualizations and real-time data tracking.

## 🌟 Features

- Real-time emotion tracking dashboard
- Interactive data visualization
- Hardware status monitoring
- Historical emotion data analysis
- User-friendly configuration interface
- Customizable monitoring dashboards
- Real-time hardware status updates

## 🛠 Tech Stack

- TypeScript
- React
- Vite
- WebSocket for real-time updates
- D3.js for data visualization
- TailwindCSS for styling
- Zustand for state management

## 📦 Installation

1. Install dependencies:
```bash
pnpm install
```

2. Set up environment variables:
```bash
cp .env.example .env
# Configure your environment variables
```

3. Start the development server:
```bash
pnpm run dev
```

## 🔧 Configuration

Configure the frontend through environment variables:

- `VITE_API_URL`: Backend API URL
- `VITE_WS_URL`: WebSocket server URL
- `VITE_REFRESH_INTERVAL`: Data refresh interval
- `VITE_THEME`: UI theme configuration

## 📊 Dashboard Features

### Emotion Monitoring

- Real-time emotion state visualization
- Historical emotion trends
- Emotion transition analysis
- Custom date range selection
- Export capabilities

### Hardware Status

- Device connection status
- System health metrics
- Performance monitoring
- Resource utilization
- Error logging and alerts

### Data Analysis

- Emotion pattern recognition
- Statistical analysis
- Custom metric tracking
- Data export tools
- Comparative analysis

## 🎨 UI Components

### Emotion Dashboard

```typescript
// Example emotion chart component
<EmotionChart
  data={emotionData}
  timeRange="24h"
  showTransitions={true}
  enableInteraction={true}
/>
```

### Hardware Monitor

```typescript
// Example hardware status component
<HardwareStatus
  deviceId={deviceId}
  metrics={['cpu', 'memory', 'network']}
  refreshRate={5000}
/>
```

### Data Visualization

```typescript
// Example visualization component
<DataVisualizer
  dataset={emotionHistory}
  type="timeline"
  options={{
    showLegend: true,
    enableZoom: true,
    colorScheme: 'emotion'
  }}
/>
```

## 📖 Development

### Project Structure

```
src/
├── components/    # Reusable UI components
├── pages/        # Page components
├── hooks/        # Custom React hooks
├── store/        # State management
├── api/          # API integration
├── utils/        # Utility functions
├── types/        # TypeScript types
└── tests/        # Test files
```

### Development Commands

```bash
pnpm run dev           # Start development server
pnpm run build         # Build for production
pnpm run preview       # Preview production build
pnpm run test         # Run tests
pnpm run lint         # Run linter
pnpm run format       # Format code
```

### Storybook

Run Storybook to develop and test components in isolation:

```bash
pnpm run storybook
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

## 🔍 Browser Support

- Chrome (latest)
- Firefox (latest)
- Safari (latest)
- Edge (latest)

## 🤝 Contributing

1. Follow the main project's contributing guidelines
2. Write meaningful commit messages
3. Add/update tests as needed
4. Update documentation for new features
5. Ensure all tests pass before submitting PR

## 📝 License

This project is licensed under the MIT License - see the main project's LICENSE file for details.

## 🎯 Future Improvements

- Advanced data visualization options
- Custom dashboard layouts
- Real-time collaboration features
- Enhanced hardware monitoring
- Mobile responsive design
- Offline support
- Multi-language support
