var mongoose = require('mongoose');

module.exports = mongoose.model('Score', {
    score: {
        type: Number,
        default: 0
    }
});
