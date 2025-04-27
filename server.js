const express = require('express');
const app = express();
const port = 3000;

// Middleware to parse JSON bodies
app.use(express.json());

// In-memory storage for orders (replace with Firebase for persistence)
let orders = [];

// POST endpoint to receive orders from ESP32
app.post('/orders', (req, res) => {
  const order = req.body;
  if (!order.table || !order.items || !Array.isArray(order.items)) {
    return res.status(400).json({ error: 'Invalid order format' });
  }
  const orderWithTimestamp = {
    ...order,
    id: orders.length + 1,
    timestamp: new Date().toISOString(),
    status: 'Pending'
  };
  orders.push(orderWithTimestamp);
  console.log('Received order:', orderWithTimestamp);
  res.status(200).json({ message: 'Order received', orderId: orderWithTimestamp.id });
});

// GET endpoint to retrieve all orders for the dashboard
app.get('/orders', (req, res) => {
  res.json(orders);
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});